<?php
	if (isset($currentCategoryID))
	{
		$categories = array();
		$category = new Category($currentCategoryID);
		$categories[] = $category->getName();
		
		while($category->getParentID())
		{
			$category = new Category($category->getParentID());
			$categories[] = $category->getName();
		}
		
		
		$categories = array_reverse($categories);

		echo "<div class=\"breadcrumbs\">";
		foreach($categories as $name) { echo "$name - "; }
		echo "</div>";
	}
?>