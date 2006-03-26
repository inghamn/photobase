<?php
/*
	$_GET variables:	categoryID
*/
	verifyUser("Administrator");
	
	require_once(APPLICATION_HOME."/classes/Category.inc");
	$category = new Category($_GET['catgoryID']);
	$category->delete();

	Header("Location: home.php");
?>