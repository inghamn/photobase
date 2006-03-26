<?php
/*
	Saves a new category to the database

	$_POST variables:	parentID
						name
*/
	verifyUser("Administrator");
	
	require_once(APPLICATION_HOME."/classes/Category.inc");
	$category = new Category();
	$category->setName($_POST['name']);
	$category->setParentID($_POST['parentID']);
	
	try { $category->save(); }
	catch (Exception $e)
	{
		$_SESSION['errorMessages'][] = $e;
		Header("Location: addCategoryForm.php?parentID=$_POST[parentID]");
		exit();
	}

	Header("Location: home.php");
?>