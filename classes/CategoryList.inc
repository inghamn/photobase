<?php
	class CategoryList extends MySQLResultIterator implements RecursiveIterator
	{
		public function find($fields=null,$sort="name")
		{
			if ($fields)
			{
				$options = array();
				if (isset($fields['categoryID'])) { $options[] = "categoryID=$fields[categoryID]"; }
				if (isset($fields['category'])) { $options[] = "category='$fields[category]'"; }
				if (isset($fields['parentID'])) { $options[] = "parentID=$fields[parentID]"; }
				
				$where = "where ".implode(" and ",$options);
				$sql = "select categoryID from categories $where order by $sort";
			}
			else { $sql = "select categoryID from categories order by $sort"; }

			$this->result = mysql_query($sql) or die($sql.mysql_error());
		}
		
		public function loadCurrent()
		{
			list($categoryID) = mysql_fetch_array($this->result);
			$this->current = new Category($categoryID);
		}
		
		public function getChildren() { return $this->current->getChildren(); }
		public function hasChildren() { return $this->current->hasChildren(); }
	}
?>