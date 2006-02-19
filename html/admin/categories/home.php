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
	<h1><button type="button" class="addSmall" onclick="document.location.href='addCategoryForm.php?parent_category=0';">Add</button>
		Categories
	</h1>
	<?php
		print_category_children(0);

		function print_category_children($category)
		{
			$sql = "select category_id,category from categories where parent_category=$category order by category";
			$temp = mysql_query($sql) or die($sql.mysql_error());
			if (mysql_num_rows($temp))
			{
				echo "<ul>";
				while (list($category_id,$category) = mysql_fetch_array($temp))
				{
					echo "
					<li><button type=\"button\" class=\"addSmall\" onclick=\"document.location.href='addCategoryForm.php?parent_category=$category_id';\">Add</button>
						<button type=\"button\" class=\"editSmall\" onclick=\document.location.href='updateCategoryForm.php?category_id=$category_id';\">Edit</button>
						<button type=\"button\" class=\"deleteSmall\" onclick=\"deleteConfirmation('deleteCategory.php?category_id=$category_id');\">Delete</button>
						$category
					";
					print_category_children($category_id);
					echo "</li>";
				}
				echo "</ul>";
			}
		}
	?>
</div>

<?php include(APPLICATION_HOME."/includes/xhtmlFooter.inc"); ?>
