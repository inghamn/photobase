<?php
/*
	Updates a category in the database

	$_POST variables:	category_id
						category
*/
	verifyUser("Administrator");

	$_POST['category'] = sanitizeString($_POST['category']);
	if (!$_POST['category'])
	{
		Header("Location: home.php");
	}

	$sql = "update categories set category='$_POST[category]' where category_id=$_POST[category_id]";
	mysql_query($sql) or die($sql.mysql_error());

	Header("Location: home.php");
?>

