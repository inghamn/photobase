<?php
	class Category
	{
		private $categoryID;
		private $category;
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
					$this->category = $category['category'];
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
			if (mysql_num_rows($sql)) { return true; }
			else { return false; }
		}
		
		public function getCategoryID() { return $this->categoryID; }
		public function getCategory() { return $this->category; }
		public function getParentID() { return $this->parentID; }
		
		public function setCategory($string) { $this->category = sanitizeString($string); }
		public function setParentID($int) { $this->parentID = $int; }
	}
?>