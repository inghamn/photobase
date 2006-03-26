<?php
	require_once(APPLICATION_HOME."/classes/CategoryList.inc");
	class Category
	{
		private $categoryID;
		private $name;
		private $parentID;
		
		public function __construct($id)
		{
			if (is_numeric($id))
			{
				$sql = "select * from categories where categoryID=$id";
				$result = mysql_query($sql) or die($sql.mysql_error());
				if (mysql_num_rows($result))
				{
					$category = mysql_fetch_array($result);
					$this->categoryID = $id;
					$this->name = $category['name'];
					if ($category['parentID']) { $this->parentID = $category['parentID']; }
				}
				else { throw new Exception($sql); }
			}
		}
		
		public function getChildren()
		{
			$categoryList = new CategoryList();
			$categoryList->find(array('parentID'=>$this->categoryID));
			return $categoryList;
		}
		
		public function hasChildren()
		{
			$sql = "select categoryID from categories where parentID={$this->categoryID}";
			$result = mysql_query($sql) or die($sql.mysql_error());
			if (mysql_num_rows($result)) { return true; }
			else { return false; }
		}
		
		public function save()
		{
			# Check for required properties
			if ($this->name)
			{
				if ($this->categoryID) { $this->update(); }
				else { $this->insert(); }
			}
			else { throw new Exception("missingName"); }
		}
		
		public function delete()
		{
			$sql = "delete from photoCategories where categoryID={$this->categoryID}";
			mysql_query($sql) or die($sql.mysql_error());
			
			$sql = "delete from categories where categoryID={$this->categoryID}";
			mysql_query($sql) or die($sql.mysql_error());
		}
		
		private function update()
		{
			$sql = "update categories set name='{$this->name}'";
			if ($this->parentID) { $sql.=",parentID={$this->parentID}"; } else { $sql.=",parentID=null"; }
			$sql.=" where categoryID={$this->categoryID}";
			mysql_query($sql) or die($sql.mysql_error());
		}
		
		private function insert()
		{
			$sql = "insert categories set name='{$this->name}'";
			if ($this->parentID) { $sql.=",parentID={$this->parentID}"; }
			mysql_query($sql) or die($sql.mysql_error());
			$this->categoryID = mysql_insert_id();
		}
		
		public function getCategoryID() { return $this->categoryID; }
		public function getName() { return $this->name; }
		public function getParentID() { return $this->parentID; }
		
		public function setName($string) { $this->name = sanitizeString($string); }
		public function setParentID($int) { $this->parentID = $int; }
	}
?>