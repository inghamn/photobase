<?php
include APPLICATION_HOME.'/xhtmlHeader.inc';
include APPLICATION_HOME.'/includes/banner.inc';
?>
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