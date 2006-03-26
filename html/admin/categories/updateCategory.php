<?php
/*
	Updates a category in the database

	$_POST variables:	categoryID
						name
*/
	verifyUser("Administrator");
	
	require_once(APPLICATION_HOME."/classes/Category.inc");
	$category = new Category($_POST['categoryID']);
	$category->setName($_POST['name']);
	try { $category->save(); }
	catch (Exception $e)
	{
		$_SESSION['errorMessages'][] = $e;
		Header("Location: updateCategoryForm.php?categoryID=$_POST[categoryID]");
		exit();
	}

	Header("Location: home.php");
?>