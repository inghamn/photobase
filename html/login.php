<?php
/*
	Logs a user into the system.
	A logged in user will have	$_SESSION[USER]
								$_SESSION[IP_ADDRESS]

	$_POST Variables:	username
						password
*/
	echo APPLICATION_HOME;
	try
	{
		$user = new User($_POST['username']);
		$user->authenticate($_POST['password']);
		$user->startNewSession();
	}
	catch (Exception $e)
	{
		$_SESSION['errorMessages'][] = $e;
	}

	Header("Location: home.php");
?>