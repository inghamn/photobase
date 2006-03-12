<?php
	require_once(APPLICATION_HOME."/classes/Category.inc");
	class Photo
	{
		private $photoID;
		private $filename;
		private $date;
		private $city;
		private $state;
		private $country;
		private $keywords;
		private $caption;
		private $notes;
		
		private categories = array();
		
		public function __construct($id=null)
		{
			if (is_numeric($id))
			{
				$sql = "select * from photos where photoID=$id";
				$result = mysql_query($sql) or die($sql.mysql_error());
				if (mysql_num_rows($result))
				{
					$photo = mysql_fetch_array($result);
					$this->photoID = $id;
					$this->filename = $photo['filename'];
					$this->date = $photo['date'];
					if ($photo['city']) { $this->city = $photo['city']; }
					if ($photo['state']) { $this->state = $photo['state']; }
					if ($photo['country']) { $this->country = $photo['country']; }
					if ($photo['keywords']) { $this->keywords = $photo['keywords']; }
					if ($photo['caption']) { $this->caption = $photo['caption']; }
					if ($photo['notes']) { $this->notes = $photo['notes']; }
					
					$this->loadCategories();
				}
				else { throw new Exception($sql); }
			}
		}
		
		public function save()
		{
			if ($this->photoID) { $this->update(); }
			else { $this->insert(); }
			
			$this->saveCategories();
		}
		
		public function addCategory($id)
		{
			foreach($this->categories as $category) { if ($category->getCategoryID() == $id) return false; }
			$this->categories[] = new Category($id);
		}
		public function deleteCategory($id) { foreach($categories as $i=>$c) { if ($c->getID() == $Id) unset($this->categories[$i]); } }
		
		private function loadCategories()
		{
			$this->categories = array();
			$sql = "select categoryID from photoCategories where photoID={$this->photoID}";
			$result = mysql_query($sql) or die($sql.mysql_error());
			while(list($categoryID) = mysql_fetch_array($result))
			{
				$this->categories[] = new Category($categoryID);
			}
		}
		private function saveCategories()
		{
			$sql = "delete from photoCategories where photoID={$this->photoID}";
			mysql_query($sql) or die($sql.mysql_error());
			
			foreach($this->categories as $category)
			{
				$sql = "insert photoCategories values({$this->photoID},{$category->getCategoryID()})";
				mysql_query($sql) or die($sql.mysql_error());
			}
		}

		private function update()
		{
			$sql = "update photos set filename='{$this->filename}'";
			if ($this->date) { $sql.=",date='{$this->date}'"; } else { $sql.=",date=null"; }
			if ($this->city) { $sql.=",city='{$this->city}'"; } else {$sql.=",city=null"; }
			if ($this->state) { $sql.=",state='{$this->state}'"; } else { $sql.=",state=null"; }
			if ($this->country) { $sql.=",country='{$this->country}'"; } else { $sql.=",country=null"; }
			if ($this->keywords) { $sql.=",keywords='{$this->keywords}'"; } else { $sql.=",keywords=null"; }
			if ($this->caption) { $sql.=",caption='{$this->caption}'"; } else { $sql.=",caption=null"; }
			if ($this->notes) { $sql.=",notes='{$this->notes}'"; } else { $sql.=",notes=null"; }
			$sql.=" where photoID={$this->photoID}";
			
			mysql_query($sql) or die($sql.mysql_error());
		}
		
		private function insert()
		{
			$sql = "insert photos set filename='{$this->filename}'";
			if ($this->date) { $sql.=",date='{$this->date}'"; } else { $sql.=",date=null"; }
			if ($this->city) { $sql.=",city='{$this->city}'"; } else {$sql.=",city=null"; }
			if ($this->state) { $sql.=",state='{$this->state}'"; } else { $sql.=",state=null"; }
			if ($this->country) { $sql.=",country='{$this->country}'"; } else { $sql.=",country=null"; }
			if ($this->keywords) { $sql.=",keywords='{$this->keywords}'"; } else { $sql.=",keywords=null"; }
			if ($this->caption) { $sql.=",caption='{$this->caption}'"; } else { $sql.=",caption=null"; }
			if ($this->notes) { $sql.=",notes='{$this->notes}'"; } else { $sql.=",notes=null"; }
			
			mysql_query($sql) or die($sql.mysql_error());
			$this->photoID = mysql_insert_id();
		}
		
		
		public function getPhotoID() { return $this->photoID; }
		public function getFilename() { return $this->filename; }
		public function getDate() { return $this->date; }
		public function getCity() { return $this->city; }
		public function getState() { return $this->state; }
		public function getCountry() { return $this->country; }
		public function getKeywords() { return $this->keywords; }
		public function getCaption() { return $this->caption; }
		public function getNotes() { return $this->notes; }
		
		public function getCategories() { return $this->categories; }
		
		public function setFilename($path) { $this->filename = $path; }
		public function setDate($date) { $this->date = $date; }
		public function setCity($string) { $this->city = sanitizeString($string); }
		public function setState($string) { $this->state = sanitizeString($string); }
		public function setCountry($string) { $this->country = sanitizeString($string); }
		public function setKeywords($string) { $this->keywords = sanitizeString($string); }
		public function setCaption($string) { $this->caption = sanitizeString($string); }
		public function setNotes($string) { $this->notes = sanitizeString($string); }
	}
?>