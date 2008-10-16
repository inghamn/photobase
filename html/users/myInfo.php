<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
verifyUser();

if (isset($_POST['user']))
{
	$_SESSION['USER']->setFirstname($_POST['user']['firstname']);
	$_SESSION['USER']->setLastname($_POST['user']['lastname']);
	$_SESSION['USER']->setEmail($_POST['user']['email']);
	if (trim($_POST['password']))
	{
		if (trim($_POST['password']) == $_POST['retypePassword'])
		{
			$_SESSION['USER']->setPassword($_POST['password']);
		}
		else
		{
			$_SESSION['errorMessages'][] = new Exception('passwordsDontMatch');
		}
	}
	try
	{
		$_SESSION['USER']->save();
		if (!isset($_SESSION['errorMessages']))
		{
			Header('Location: '.BASE_URL);
			exit();
		}
	}
	catch (Exception $e) { $_SESSION['errorMessages'][] = $e; }
}

$template = new Template();
$template->blocks[] = new Block('users/updateMyInfoForm.inc',array('user'=>$_SESSION['USER']));
echo $template->render();