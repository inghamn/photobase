<?php
/*
	Logs a user into the system.
	A logged in user will have	$_SESSION[USER_ID]
								$_SESSION[IP_ADDRESS]
								$_SESSION[ROLES]

	$_POST Variables:	username
						password
*/
	# Clear out any old session
	session_destroy();
	session_start();

	$sql = "select user_id from users where username='$_POST[username]' and password=md5('$_POST[password]')";
	$result = mysql_query($sql) or die($sql.mysql_error());
	if (mysql_num_rows($result))
	{
		list($user_id) = mysql_fetch_array($result);

		# They're good to go, log them into the site
		$_SESSION['USER_ID'] = $user_id;
		$_SESSION['IP_ADDRESS'] = $_SERVER['REMOTE_ADDR'];

		$roles = array();
		$sql = "select role from user_roles where user_id=$_SESSION[USER_ID]";
		$roles = mysql_query($sql) or die($sql.mysql_error());
		while(list($role) = mysql_fetch_array($roles))
		{
			$_SESSION['ROLES'][] = $role;
		}
	}

	Header("Location: home.php");
?>
