<?php
/*
	$_GET variables:	parent_category
*/
	verifyUser("Administrator");

	include(APPLICATION_HOME."/includes/xhtmlHeader.inc");
	include(APPLICATION_HOME."/includes/banner.inc");
	include(APPLICATION_HOME."/includes/toolboxes/admin.inc");

	$current_category = $_GET['parent_category'];
	include(APPLICATION_HOME."/includes/category_breadcrumbs.inc");
?>

<div id="mainContent">
	<h1>Add a category</h1>
	<form method="post" action="addCategory.php">
	<fieldset><legend>Category Info</legend>
		<input name="parent_category" type="hidden" value="<?php echo $_GET['parent_category']; ?>" />

		<table>
		<tr><td><label for="category">New Category</label></td>
			<td><input name="category" id="category" /></td></tr>
		</table>

		<button type="submit" class="submit">Submit</button>
		<button type="button" class="cancel" onclick="document.location.href='home.php';">Cancel</button>
	</fieldset>
	</form>
</div>

<?php include(APPLICATION_HOME."/includes/xhtmlFooter.inc"); ?>
