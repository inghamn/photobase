<?php
/*
	Saves a new category to the database

	$_POST variables:	parent_category
						category
*/
	verifyUser("Administrator");

	$_POST['category'] = sanitizeString($_POST['category']);
	if (!$_POST['category'])
	{
		Header("Location: home.php");
	}

	$sql = "insert categories set category='$_POST[category]',parent_category=$_POST[parent_category]";
	mysql_query($sql) or die($sql.mysql_error());

	Header("Location: home.php");
?>
