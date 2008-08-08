<?php
include APPLICATION_HOME.'/xhtmlHeader.inc';
include APPLICATION_HOME.'/includes/banner.inc';
?>
<div id="sidebar">
	<?php
		include APPLICATION_HOME.'/includes/sidebarBoxes/Categories.inc';
		include APPLICATION_HOME.'/includes/sidebarBoxes/Rolls.inc';
		
		if (userHasRole('Administrator'))
		{
			include APPLICATION_HOME.'/includes/sidebarBoxes/Administrator.inc';
		}

	?>
</div>
<div id="mainContent">
	<?php
		include FRAMEWORK.'/errorMessages.inc';

		echo $this->includeBlocks();
	?>
</div>
<?php
include APPLICATION_HOME.'/includes/footer.inc';
include APPLICATION_HOME.'/xhtmlFooter.inc';
?>