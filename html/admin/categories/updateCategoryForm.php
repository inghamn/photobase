<?php
/*
	$_GET variables:	category_id
*/
	verifyUser("Administrator");

	include(APPLICATION_HOME."/includes/xhtmlHeader.inc");
	include(APPLICATION_HOME."/includes/banner.inc");
	include(APPLICATION_HOME."/includes/toolboxes/admin.inc");

	$sql = "select * from categories where category_id=$_GET[category_id]";
	$category = mysql_fetch_array(mysql_query($sql)) or die($sql.mysql_error());
?>

<div id="mainContent">
	<h1>Edit a category</h1>
	<form method="post" action="updateCategory.php">
	<fieldset><legend>Category Info</legend>
		<input name="category_id" type="hidden" value="<?php echo $_GET['category_id']; ?>" />

		<table>
		<tr><td><label for="category">Category</label></td>
			<td><input name="category" id="category" value="<?php echo $category['category']; ?>" /></td></tr>
		</table>

		<button type="submit" class="submit">Submit</button>
		<button type="button" class="cancel" onclick="document.location.href='home.php';">Cancel</button>
	</fieldset>
	</form>
</div>

<?php include(APPLICATION_HOME."/includes/xhtmlFooter.inc"); ?>

