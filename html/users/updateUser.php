<?php
/*
	$_POST variables:	userID
						username
						firstname
						lastname
						roles
						password	(optional)
*/
	verifyUser("Administrator");

	$user = new User($_POST['userID']);
	$user->setUsername($_POST['username']);
	$user->setFirstname($_POST['firstname']);
	$user->setLastname($_POST['lastname']);
	$user->setRoles($_POST['roles']);

	if ($_POST['password']) { $user->setPassword($_POST['password']); }

	try
	{
		$user->save();
		Header("Location: home.php");
	}
	catch (Exception $e)
	{
		$_SESSION['errorMessages'][] = $e;
		Header("Location: addUserForm.php");
	}
?>