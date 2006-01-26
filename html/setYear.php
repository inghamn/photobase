<?php
	session_start();

	$_SESSION['YEAR'] = $_POST['year'];

	Header("Location: home.php");
?>