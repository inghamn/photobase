<?php
	/* This deletes a photo and sends them back to the grid. There is no
		verification.  And it rely's on Apache to verify the user with
		the .htaccess file.  They shouldn't get to this script if they're not
		supposed to be able to delete a photo.

	$_GET Variables:	photo

	Called From:	grid.php
	*/

	mysql_connect("localhost","username","password");
	mysql_select_db("database") or die(mysql_error());

?>