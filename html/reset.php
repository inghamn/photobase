<?php
	session_start();
	session_unset();
	
	Header("Location: home.php");
?>