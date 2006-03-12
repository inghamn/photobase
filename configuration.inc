<?php
/*
	Global configuration options for the photo database
*/

	define("APPLICATION_HOME","/var/www/sites/album");	# Where on the filesystem this is installed
	define("BASE_URL","/album");						# The base URL to get to this site on this webserver

	#----------------------------------------------------------------------------
	# Go ahead and make a database connection here.
	#----------------------------------------------------------------------------
	define("MYSQL_LOCATION",":/tmp/mysql.sock");
	define("MYSQL_USER","username");
	define("MYSQL_PASS","password");
	define("MYSQL_DATABASE","album");

	mysql_connect(MYSQL_LOCATION,MYSQL_USER,MYSQL_PASS) or die(mysql_error());
	mysql_select_db(MYSQL_DATABASE) or die(mysql_error());

	#----------------------------------------------------------------------------
	# Since sessions are going to be storing a User object, we need to load the class
	#----------------------------------------------------------------------------
	require_once(APPLICATION_HOME."/classes/User.inc");
	session_start();
	

	include(APPLICATION_HOME."/classes/globalFunctions.inc");
?>
