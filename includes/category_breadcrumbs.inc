<?php
	if (isset($current_category))
	{
		$categories = array();
		$categories = getCategories($current_category,$categories);
		$categories = array_reverse($categories);

		echo "<div class=\"breadcrumbs\">";
		foreach($categories as $category)
		{
			echo "$category[category] - ";
		}
		echo "</div>";
	}

	function getCategories($category_id,$categories)
	{
		$sql = "select * from categories where category_id=$category_id";
		$category = mysql_fetch_array(mysql_query($sql)) or die($sql.mysql_error());
		$categories[] = $category;

		if ($category['parent_category'])
		{
			$categories = getCategories($category['parent_category'],$categories);
		}

		return $categories;
	}

?>
