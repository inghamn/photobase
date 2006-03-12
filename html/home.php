<?php
	include(APPLICATION_HOME."/includes/xhtmlHeader.inc");
	include(APPLICATION_HOME."/includes/banner.inc");
	include(APPLICATION_HOME."/includes/controls.inc");
	include(APPLICATION_HOME."/includes/categories.inc");

	if (!isset($_SESSION['USER_ID']) || !$_SESSION['USER_ID']) { include(APPLICATION_HOME."/includes/toolboxes/loginForm.inc"); }
	if(isset($_SESSION['ROLES']) && in_array("Administrator",$_SESSION['ROLES'])) { include (APPLICATION_HOME."/includes/toolboxes/admin.inc"); }
?>

<div id="mainContent">
	<?php
		$photoList = new PhotoList();
		$photoList->find();
		foreach($photoList as $photo)
		{
			echo "<div>$photo->getName();</div>";
		}
	?>
</div>

<?php include(APPLICATION_HOME."/includes/xhtmlFooter.inc"); ?>