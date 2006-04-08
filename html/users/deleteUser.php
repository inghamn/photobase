<?php
/*
	$_GET variables: 	userID
*/
	verifyUser("Administrator");

	$user = new User($_GET['userID']);
	$user->delete();

	Header("Location: home.php");
?>