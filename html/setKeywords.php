<?php
	session_start();

	$_SESSION['KEYWORDS'] = $_POST['keywords'];

	Header("Location: home.php");
?>