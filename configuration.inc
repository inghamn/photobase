<?php
/*
	Global configuration options for the photo database
*/
	session_start();

	$APPLICATION_HOME = "/var/www/sites/album";	# Where on the filesystem this is installed
	$BASE_URL = "/album";						# The base URL to get to this site on this webserver

	$MYSQL_LOCATION = ":/tmp/mysql.sock";
	$MYSQL_USER = "username";
	$MYSQL_PASS = "password";
	$MYSQL_DATABASE = "album";

	mysql_connect($MYSQL_LOCATION,$MYSQL_USER,$MYSQL_PASS) or die(mysql_error());
	mysql_select_db($MYSQL_DATABASE) or die(mysql_error());
?>
