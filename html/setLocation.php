<?php
	$_SESSION['STATE'] = $_POST['state'];

	Header("Location: home.php");
?>