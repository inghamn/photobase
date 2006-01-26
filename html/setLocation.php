<?php
	session_start();

	$_SESSION['STATE'] = $_POST['state'];

	Header("Location: home.php");
?>