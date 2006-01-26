<?php
	$_SESSION['YEAR'] = 0;

	$_SESSION['FIRSTREC'] = $_GET['firstRec'];

	Header("Location: home.php");
?>