<?php
/**
 * @copyright Copyright (C) 2008 Cliff Ingham. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * Represents a directory of uploaded media to be added to the database
 */
class UserUploadDirectory Implements Countable,IteratorAggregate
{
	private $user;

	public function __construct(User $user)
	{
		$this->user = $user;
		if (!is_dir($this->getDirectory()))
		{
			mkdir($this->getDirectory(),0777);
		}
	}

	public function import($rollname)
	{
		$roll = new Roll();
		$roll->setName($rollname);
		$roll->setUser($this->user);
		$roll->save();

		foreach(glob($this->getDirectory().'/*.*') as $file)
		{
			$media = new Media();
			$media->setRoll_id($roll->getId());
			$media->setUser($this->user);
			$media->setFile($file);
			$media->save();
		}

		foreach(glob($this->getDirectory().'/thumbnail/*.*') as $thumbnail)
		{
			unlink($thumbnail);
		}

		return $roll;
	}

	public function getDirectory() { return APPLICATION_HOME.'/uploads/'.$this->user->getUsername(); }


	# Countable Section
	public function count() { return count(glob($this->getDirectory().'/*.*')); }

	public function getIterator() { return new DirectoryIterator($this->getDirectory()); }

	public function add($file)
	{
		echo "Adding file";
		if (is_array($file))
		{
			$filename = Media::createValidFilename($file['name']);
			if (Media::isValidFiletype($filename))
			{
				echo "Adding {$this->getDirectory()}/$filename";
				if (!move_uploaded_file($file['tmp_name'],"{$this->getDirectory()}/$filename"))
				{
					throw new Exception('uploads/failedAddingFile');
				}
			}
			else
			{
				throw new Exception('uploads/invalidFiletype');
			}
		}
		elseif(is_file($file))
		{
			$filename = Media::createValidFilename(basename($file));
			if (Media::isValidFiletype($filename))
			{
				rename($file,"{$this->getDirectory()}/$filename");
			}
			else
			{
				throw new Exception('uploads/invalidFiletype');
			}
		}
	}
}
