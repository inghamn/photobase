<?php
/*
	$_GET variables:	category_id
*/
	verifyUser("Administrator");

	$sql = "delete from categories where category_id=$_GET[category_id]";
	mysql_query($sql) or die($sql.mysql_error());

	Header("Location: home.php");
?>
