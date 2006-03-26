<?php
/*
	$_GET variables:	categoryID
*/
	verifyUser("Administrator");

	include(APPLICATION_HOME."/includes/xhtmlHeader.inc");
	include(APPLICATION_HOME."/includes/banner.inc");
	include(APPLICATION_HOME."/includes/toolboxes/admin.inc");

	require_once(APPLICATION_HOME."/classes/Category.inc");
	$category = new Category($_GET['categoryID']);
?>

<div id="mainContent">
	<h1>Edit a category</h1>
	<form method="post" action="updateCategory.php">
	<fieldset><legend>Category Info</legend>
		<input name="categoryID" type="hidden" value="<?php echo $_GET['categoryID']; ?>" />

		<table>
		<tr><td><label for="name">Category</label></td>
			<td><input name="name" id="name" value="<?php echo $category->getName(); ?>" /></td></tr>
		</table>

		<button type="submit" class="submit">Submit</button>
		<button type="button" class="cancel" onclick="document.location.href='home.php';">Cancel</button>
	</fieldset>
	</form>
</div>

<?php include(APPLICATION_HOME."/includes/xhtmlFooter.inc"); ?>