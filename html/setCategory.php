<?php
	session_start();

	$_SESSION['CATEGORY'] = $_GET['category'];

	Header("Location: home.php");
?>