<?php
	require_once(APPLICATION_HOME."/classes/CategoryList.inc");
	function print_category_children($parentID)
	{
		$categories = new CategoryList();
		$categories->find( array("parentID"=>$parentID) );
		if (count($categories))
		{
			echo "<ul>";
			foreach($categories as $category)
			{
				echo "<li><a href=\"setCategory.php=categoryID={$category->getCategoryID()}\">{$category->getName()}</a>";
				if ($category->hasChildren()) { print_category_children($category->getCategoryID()); }
				echo "</li>";
			}
			echo "</ul>";
		}
	}
?>
<div class="sidebar">
	<div class="titleBar">Categories</div>
	<?php print_category_children(0); ?>
</div>