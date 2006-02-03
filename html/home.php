<?php
	include("$APPLICATION_HOME/includes/xhtmlHeader.inc");
	include("$APPLICATION_HOME/includes/banner.inc");
	include("$APPLICATION_HOME/includes/controls.inc");
	include("$APPLICATION_HOME/includes/categories.inc");

	if (!isset($_SESSION['USER_ID']) || !$_SESSION['USER_ID']) { include("$APPLICATION_HOME/includes/toolboxes/loginForm.inc"); }
	if(isset($_SESSION['ROLES']) && in_array("Administrator",$_SESSION['ROLES'])) { include ("$APPLICATION_HOME/includes/toolboxes/admin.inc"); }
?>

<div id="mainContent">
	<?php
		print_r($_SESSION);
		include("$APPLICATION_HOME/includes/thumbnails.inc");
	?>
</div>

<?php include("$APPLICATION_HOME/includes/xhtmlFooter.inc"); ?>