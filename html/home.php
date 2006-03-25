<?php
	include(APPLICATION_HOME."/includes/xhtmlHeader.inc");
	include(APPLICATION_HOME."/includes/banner.inc");
	include(APPLICATION_HOME."/includes/controls.inc");
	include(APPLICATION_HOME."/includes/categories.inc");

	if (!isset($_SESSION['USER'])) { include(APPLICATION_HOME."/includes/toolboxes/loginForm.inc"); }
	if(isset($_SESSION['USER']) && in_array("Administrator",$_SESSION['USER']->getRoles())) { include (APPLICATION_HOME."/includes/toolboxes/admin.inc"); }
?>

<div id="mainContent">
	<?php
		require_once(APPLICATION_HOME."/classes/PhotoList.inc");
		$photoList = new PhotoList();
		$photoList->find();
		foreach($photoList as $photo)
		{
			echo "
			<div><img src=\"smalls/{$photo->getFilename()}\" alt=\"{$photo->getFilename()}\" />
				<p>{$photo->getDate()}</p>
			</div>
			";
		}
	?>
</div>

<?php include(APPLICATION_HOME."/includes/xhtmlFooter.inc"); ?>