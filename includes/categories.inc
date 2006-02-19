<?php
	function print_category_children($category)
	{
		$sql = "select category_id,category from categories where parent_category=$category order by category";
		$temp = mysql_query($sql) or die($sql.mysql_error());
		if (mysql_num_rows($temp))
		{
			echo "<ul>";
			while (list($category_id,$category) = mysql_fetch_array($temp))
			{
				echo "<li><a href=\"setCategory.php=category_id=$category_id\">$category</a>";
				print_category_children($category_id);
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