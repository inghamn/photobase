<?php
/*
	$_GET variables:	parentID
*/
	verifyUser("Administrator");

	include(APPLICATION_HOME."/includes/xhtmlHeader.inc");
	include(APPLICATION_HOME."/includes/banner.inc");
	include(APPLICATION_HOME."/includes/toolboxes/admin.inc");

	if ($_GET['parentID'])
	{
		require_once(APPLICATION_HOME."/classes/Category.inc");
		$currentCategoryID = $_GET['parentID'];
		include(APPLICATION_HOME."/includes/category_breadcrumbs.inc");
	}
?>
<div id="mainContent">
	<h1>Add a category</h1>
	<form method="post" action="addCategory.php">
	<fieldset><legend>Category Info</legend>
		<input name="parentID" type="hidden" value="<?php echo $_GET['parentID']; ?>" />

		<table>
		<tr><td><label for="name">New Category</label></td>
			<td><input name="name" id="name" /></td></tr>
		</table>

		<button type="submit" class="submit">Submit</button>
		<button type="button" class="cancel" onclick="document.location.href='home.php';">Cancel</button>
	</fieldset>
	</form>
</div>

<?php include(APPLICATION_HOME."/includes/xhtmlFooter.inc"); ?>