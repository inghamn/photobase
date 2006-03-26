<?php
/*
	Shows the tree of categories so we can work with them
*/
	verifyUser("Administrator");

	include(APPLICATION_HOME."/includes/xhtmlHeader.inc");
	include(APPLICATION_HOME."/includes/banner.inc");
	include(APPLICATION_HOME."/includes/toolboxes/admin.inc");
?>

<div id="mainContent">
	<h1><button type="button" class="addSmall" onclick="document.location.href='addCategoryForm.php?parentID=0';">Add</button>
		Categories
	</h1>
	<?php
		require_once(APPLICATION_HOME."/classes/CategoryList.inc");
		print_category_children(0);
		function print_category_children($parentID)
		{
			$categories = new CategoryList();
			$categories->find( array("parentID"=>$parentID) );
			if (count($categories))
			{
				echo "<ul>";
				foreach($categories as $category)
				{
					echo "
					<li><button type=\"button\" class=\"addSmall\" onclick=\"document.location.href='addCategoryForm.php?parentID={$category->getCategoryID()}';\">Add</button>
						<button type=\"button\" class=\"editSmall\" onclick=\"document.location.href='updateCategoryForm.php?categoryID={$category->getCategoryID()}';\">Edit</button>
						<button type=\"button\" class=\"deleteSmall\" onclick=\"deleteConfirmation('deleteCategory.php?categoryID={$category->getCategoryID()}');\">Delete</button>
						{$category->getName()}
					";
					if ($category->hasChildren()) { print_category_children($category->getCategoryID()); }
					echo "</li>";
				}
				echo "</ul>";
			}
		}
	?>
</div>

<?php include(APPLICATION_HOME."/includes/xhtmlFooter.inc"); ?>