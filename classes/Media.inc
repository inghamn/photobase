<?php
/**
 * @copyright Copyright (C) 2007 Cliff Ingham. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
class Media extends ActiveRecord
{
	private $id;
	private $filename;
	private $mime_type;
	private $media_type;
	private $title;
	private $description;
	private $md5;
	private $user_id;
	private $roll_id;
	private $date;
	private $city;
	private $state;
	private $country;
	private $notes;

	private $user;
	private $roll;

	private $currentDirectory;
	private $tags = array();

	private static $sizes = array('medium'=>array('size'=>350,'ext'=>'jpg'),
						   'thumbnail'=>array('size'=>200,'ext'=>'gif')
						   );

	public static $extensions = array(	'jpg'=>array('mime_type'=>'image/jpeg','media_type'=>'image'),
										'gif'=>array('mime_type'=>'image/gif','media_type'=>'image'),
										'png'=>array('mime_type'=>'image/png','media_type'=>'image'),
										'tiff'=>array('mime_type'=>'image/tiff','media_type'=>'image'),
										'wmv'=>array('mime_type'=>'video/x-ms-wmv','media_type'=>'video'),
										'mov'=>array('mime_type'=>'video/quicktime','media_type'=>'video'),
										'rm'=>array('mime_type'=>'application/vnd.rn-realmedia','media_type'=>'video'),
										'ram'=>array('mime_type'=>'audio/vnd.rn-realaudio','media_type'=>'audio'),
										'mp3'=>array('mime_type'=>'audio/mpeg','media_type'=>'audio'),
										'wma'=>array('mime_type'=>'audio/x-ms-wma','media_type'=>'audio')
								);
	public static function getExtensions() { return self::$extensions; }

	/**
	 * This will load all fields in the table as properties of this class.
	 * You may want to replace this with, or add your own extra, custom loading
	 */
	public function __construct($id=null)
	{
		if ($id)
		{
			$PDO = Database::getConnection();
			$sql = 'select id,filename,mime_type,media_type,title,description,md5,user_id,roll_id,
						unix_timestamp(date) as date,city,state,country,notes from media where id=?';
			$query = $PDO->prepare($sql);
			$query->execute(array($id));

			$result = $query->fetchAll();
			if (!count($result)) { throw new Exception('media/unknownMedia'); }
			foreach($result[0] as $field=>$value) { if ($value) $this->$field = $value; }

			$this->currentDirectory = $this->getDirectory();
		}
		else
		{
			# This is where the code goes to generate a new, empty instance.
			# Set any default values for properties that need it here
		}
	}


	/**
	 * This generates generic SQL that should work right away.
	 * You can replace this $fields code with your own custom SQL
	 * for each property of this class,
	 */
	public function save()
	{
		# Check for required fields here.  Throw an exception if anything is missing.
		if (!$this->filename || !$this->mime_type || !$this->media_type) { throw new Exception('missingRequiredFields'); }
		if (!$this->roll_id) { throw new Exception('media/missingRoll'); }
		if (!$this->user_id) { throw new Exception('missingUser_id'); }

		$fields = array();
		$fields['filename'] = $this->filename;
		$fields['mime_type'] = $this->mime_type;
		$fields['media_type'] = $this->media_type;
		$fields['title'] = $this->title ? $this->title : null;
		$fields['description'] = $this->description ? $this->description : null;
		$fields['md5'] = $this->md5 ? $this->md5 : null;
		$fields['user_id'] = $this->user_id;
		$fields['roll_id'] = $this->roll_id;
		$fields['date'] = $this->date ? date('Y-m-d H:i:s',$this->date) : null;
		$fields['city'] = $this->city ? $this->city : null;
		$fields['state'] = $this->state ? $this->state : null;
		$fields['country'] = $this->country ? $this->country : null;
		$fields['notes'] = $this->notes ? $this->notes : null;

		# Split the fields up into a preparedFields array and a values array.
		# PDO->execute cannot take an associative array for values, so we have
		# to strip out the keys from $fields
		$preparedFields = array();
		foreach($fields as $key=>$value)
		{
			$preparedFields[] = "$key=?";
			$values[] = $value;
		}
		$preparedFields = implode(",",$preparedFields);


		if ($this->id) { $this->update($values,$preparedFields); }
		else { $this->insert($values,$preparedFields); }

		$this->saveFile();
	}

	private function update($values,$preparedFields)
	{
		$PDO = Database::getConnection();

		$sql = "update media set $preparedFields where id={$this->id}";
		$query = $PDO->prepare($sql);
		$query->execute($values);
	}

	private function insert($values,$preparedFields)
	{
		$PDO = Database::getConnection();

		$sql = "insert media set $preparedFields";
		$query = $PDO->prepare($sql);
		$query->execute($values);
		$this->id = $PDO->lastInsertID();
	}

	/**
	 * Cleans the filename of the given file and
	 * loads metadata about the file
	 * @param Path $file The full path to the file
	 * /var/www/sites/photobase/uploads/newRoll/something.jpg
	 */
	public function setFile($file)
	{
		if (!is_file($file)) { throw new Exception('media/invalidFile'); }

		$this->md5 = md5_file($file);
		$this->currentDirectory = dirname($file);
		$filename = basename($file);


		# Clean all bad characters from the filename
		$this->filename = $this->createValidFilename($filename);

		# Move the file to our new clean filename
		rename($file,$this->currentDirectory.'/'.$this->filename);

		if (self::isValidFiletype($this->filename))
		{
			$this->mime_type = self::$extensions[self::getExtension($this->filename)]['mime_type'];
			$this->media_type = self::$extensions[self::getExtension($this->filename)]['media_type'];
		}
		else { throw new Exception('unknownFileType'); }

		$exif = @exif_read_data($this->currentDirectory.'/'.$this->filename);
		if ($exif)
		{
			if (isset($exif['DateTime']) && $exif['DateTime'])
			{
				$this->date = strtotime($exif['DateTime']);
			}
		}
	}

	/**
	 * Moves an uploaded file to wherever files should be stored
	 */
	private function saveFile()
	{
		# Only try handle new files
		if ($this->currentDirectory != $this->getDirectory())
		{
			# Clean out any previous version of the file
			if ($this->id)
			{
				foreach(glob($this->getDirectory().'/'.$this->id.'.') as $file)
				{
					unlink($this->getDirectory().'/'.$file);
				}
			}

			# Move the file where it's supposed to go
			if (!is_dir($this->getDirectory())) { mkdir($this->getDirectory(),0777,true); }
			$targetFile = $this->getDirectory().'/'.$this->getInternalFilename();
			$newFile = $this->currentDirectory.'/'.$this->filename;
			rename($newFile,$targetFile);

			if (!is_file($this->getDirectory().'/'.$this->getInternalFilename()))
			{
				throw new Exception('media/uploadFailed');
			}

			$this->currentDirectory = $this->getDirectory();
		}
		
		#foreach(array_keys(self::$sizes) as $size) { $this->generateCustomSize($size); }

		$this->saveTags();
	}

	/**
	 * Media is stored in the rolls directory
	 */
	public function getDirectory()
	{
		if (!$this->roll_id) { throw new Exception('media/missingRoll'); }
		return APPLICATION_HOME."/html/rolls/{$this->roll_id}";
	}

	/**
	 * Returns the filename the system will use to store the media
	 * This will be different from the filename the user gave it when
	 * they uploaded it
	 */
	public function getInternalFilename()
	{
		# We've got a chicken-or-egg problem here.  We want to use the id
		# as the filename, but the id doesn't exist until the info's been saved
		# to the database.
		#
		# If we don't have an id yet, try and save to the database first.
		# If that fails, we most likely don't have enough required info yet
		if (!$this->id) { $this->save(); }
		return $this->id.'.'.self::getExtension($this->filename);
	}



	/**
	 * Returns the file size of the original media
	 */
	public function getFilesize()
	{
		return filesize($this->getDirectory().'/'.$this->getInternalFilename());
	}

	/**
	 * Returns the URL to display the media. You can optionally include
	 * the size of display you want (thumbnail,medium)
	 * @param string $size
	 */
	public function getURL($size=null)
	{
		if ($size && array_key_exists($size,self::$sizes))
		{
			$ext = self::$sizes[$size]['ext'];
			return BASE_URL."/rolls/{$this->roll_id}/$size/{$this->id}.$ext";
		}
		else
		{
			return BASE_URL."/rolls/{$this->roll_id}/{$this->getInternalFilename()}";
		}
	}

	/**
	 * Generates, caches, and outputs preview versions of media
	 * Uses Media::sizes to predefine known sizes and extensions
	 * @param string $size Must be an entry in Media::sizes
	 */
	public function output($size='medium')
	{
		if (in_array($size,array_keys(self::$sizes)))
		{
			$directory = $this->currentDirectory."/$size";
			if ($this->id) { $filename = $this->id; }
			else
			{
				preg_match('/(^.*)\.([^\.]+)$/',$this->filename,$matches);
				$filename = $matches[1];
			}

			$ext = self::$sizes[$size]['ext'];
			if (!is_file("$directory/$filename.$ext"))
			{
				self::resize($this->getDirectory().'/'.$this->getInternalFilename(),$size);
			}

			readfile("$directory/$filename.$ext");
		}
		else { throw new Exception('media/unknownSize'); }
	}
	
	/**
	 * Generates and caches preview versions of media
	 * Uses Media::sizes to predefine known sizes and extensions
	 * @param string $size Must be an entry in Media::sizes
	 */
	public function generateCustomSize($size)
	{
		if (in_array($size,array_keys(self::$sizes)))
		{
			$ext = self::$sizes[$size]['ext'];
			self::resize($this->getDirectory().'/'.$this->getInternalFilename(),$size);
		}
	}

	/**
	 * Determines whether the given user is allowed to edit anything about this media
	 * @param User $user
	 */
	public function permitsEditingBy($user)
	{
		return $user instanceof User;
	}

	public function getTags()
	{
		if (!count($this->tags))
		{
			$tags = new TagList(array('media_id'=>$this->id));
			foreach($tags as $tag)
			{
				$this->tags[$tag->getId()] = $tag;
			}
		}
		return $this->tags;
	}


	public function setTags($string)
	{
		foreach(Tag::tokenize($string) as $name)
		{
			try { $tag = new Tag($name); }
			catch (Exception $e)
			{
				$tag = new Tag();
				$tag->setName($name);
				$tag->save();
			}

			$this->tags[$tag->getId()] = $tag;
		}
	}

	private function saveTags()
	{
		$PDO = Database::getConnection();

		$query = $PDO->prepare('delete from media_tags where media_id=?');
		$query->execute(array($this->id));

		$query = $PDO->prepare('insert media_tags set media_id=?,tag_id=?');
		foreach($this->getTags() as $tag)
		{
			$query->execute(array($this->id,$tag->getId()));
		}
	}


	#----------------------------------------------------------------
	# Generic Getters
	#----------------------------------------------------------------
	public function getId() { return $this->id; }
	public function getFilename() { return $this->filename; }
	public function getMime_type() { return $this->mime_type; }
	public function getMedia_type() { return $this->media_type; }
	public function getTitle() { return $this->title; }
	public function getDescription() { return $this->description; }
	public function getMd5() { return $this->md5; }
	public function getUser_id() { return $this->user_id; }
	public function getRoll_id() { return $this->roll_id; }
	public function getCity() { return $this->city; }
	public function getState() { return $this->state; }
	public function getCountry() { return $this->country; }
	public function getNotes() { return $this->notes; }
	public function getDate($format=null)
	{
		if ($format && $this->date)
		{
			if (strpos($format,'%')!==false) { return strftime($format,$this->date); }
			else { return date($format,$this->date); }
		}
		else return $this->date;
	}

	public function getUser()
	{
		if ($this->user_id)
		{
			if (!$this->user) { $this->user = new User($this->user_id); }
			return $this->user;
		}
		else return null;
	}

	public function getRoll()
	{
		if ($this->roll_id)
		{
			if (!$this->roll) { $this->roll = new Roll($this->roll_id); }
			return $this->roll;
		}
		else return null;
	}


	#----------------------------------------------------------------
	# Generic Setters
	#----------------------------------------------------------------
	public function setFilename($string) { $this->filename = trim($string); }
	public function setMime_type($string) { $this->mime_type = trim($string); }
	public function setMedia_type($string) { $this->media_type = trim($string); }
	public function setTitle($string) { $this->title = trim($string); }
	public function setDescription($text) { $this->description = $text; }
	public function setMd5($string) { $this->md5 = trim($string); }
	public function setUser_id($int) { $this->user = new User($int); $this->user_id = $int; }
	public function setRoll_id($int) { $this->roll = new Roll($int); $this->roll_id = $int; }
	public function setCity($string) { $this->city = trim($string); }
	public function setState($string) { $this->state = trim($string); }
	public function setCountry($string) { $this->country = trim($string); }
	public function setNotes($string) { $this->notes = trim($string); }
	public function setDate($datetime)
	{
		if (is_array($datetime)) { $this->date = $this->dateArrayToTimestamp($datetime); }
		elseif(ctype_digit($datetime)) { $this->date = $datetime; }
		else { $this->date = strtotime($datetime); }
	}

	public function setUser($user) { $this->user_id = $user->getId(); $this->user = $user; }
	public function setRoll($roll) { $this->roll_id = $roll->getId(); $this->roll = $roll; }

	#----------------------------------------------------------------
	# Custom Functions
	#----------------------------------------------------------------
	public static function isValidFiletype($filename)
	{
		$ext = self::getExtension($filename);
		return array_key_exists(strtolower($ext),self::$extensions);
	}

	/**
	 * Reads the extension from the user-given filename
	 */
	public static function getExtension($filename)
	{
		preg_match("/[^.]+$/",$filename,$matches);
		return strtolower($matches[0]);
	}

	/**
	 * Converts a string into a filename that should be safe on any system
	 * @param String $string
	 */
	public static function createValidFilename($string)
	{
		# No bad characters
		$string = preg_replace('/[^A-Za-z0-9_\.\s]/','',$string);

		# Convert spaces to underscores
		$string = preg_replace('/\s+/','_',$string);

		# Lower case any file extension
		if (preg_match('/(^.*\.)([^\.]+)$/',$string,$matches))
		{
			$string = $matches[1].strtolower($matches[2]);
		}

		return $string;
	}

	/**
	 * Uses ImageMagick to create a thumbnail file for the given image
	 * Input must be a full path.
	 * The resized image file will be saved in $inputPath/$size/$inputFilename.$ext
	 * The sizes array determines the output filetype (gif,jpg,png)
	 * ie. /var/www/sites/photobase/uploads/username/something.jpg
	 * @param string $inputFile Full path to an image file
	 * @param string $size The name of the size desired.  Names are defined in the Media class
	 */
	public static function resize($inputFile,$size)
	{
		if (in_array($size,array_keys(self::$sizes)))
		{
			$directory = dirname($inputFile)."/$size";

			preg_match('/(^.*)\.([^\.]+)$/',basename($inputFile),$matches);
			$filename = $matches[1];

			$ext = self::$sizes[$size]['ext'];

			if (!is_dir($directory)) { mkdir($directory,0777,true); }

			$dimension = self::$sizes[$size]['size'];
			$newFile = "$directory/$filename.$ext";
			exec(IMAGEMAGICK."/convert $inputFile -resize '{$dimension}x{$dimension}>' $newFile");
		}
		else { throw new Exception('media/unknownSize'); }
	}

	public static function getSizes() { return self::$sizes; }
}