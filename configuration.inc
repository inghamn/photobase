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

	#----------------------------------------------------------------------------
	# Makes sure the person is currently logged into the site
	#----------------------------------------------------------------------------
	function verifyUser()
	{
		global $BASE_URL,$APPLICATION_HOME;

		# Make sure they're logged in
		if (!isset($_SESSION['USER_ID']) || $_SESSION['IP_ADDRESS']!=$_SERVER['REMOTE_ADDR'])
		{
			# They're not logged in.  Boot them out to the login page
			$_SESSION['errorMessages'][] = "notLoggedIn";
			Header("Location: $BASE_URL");
		}

		if (func_num_args() > 0)
		{
			list($role) = func_get_args();
			if (!in_array($role,$_SESSION['ROLES']))
			{
				# They're trying to go somewhere they're not supposed to
				$_SESSION['errorMessages'][] = "noAccessAllowed";
				Header("Location: $BASE_URL");
			}
		}

	}

	#----------------------------------------------------------------------------
	# There are more bad characters than htmlspecialchars deals with.  We just want
	# to add in some other characters to clean.  While here, we might as well
	# have it trim out the whitespace too.
	#----------------------------------------------------------------------------
	function sanitizeString ($string)
	{
			$string = htmlspecialchars(trim($string),ENT_QUOTES);
			$string = str_replace("\\","&#92;",$string);
			return $string;
	}?>
