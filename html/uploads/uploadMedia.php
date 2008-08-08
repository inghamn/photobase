<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param POST username
 * @param POST password
 * @param POST mediafile
 */
try
{
	$user = new User($_POST['username']);

	if ($user->authenticate($_POST['password'])) { $user->startNewSession(); }
	else { throw new Exception('wrongPassword'); }
}
catch (Exception $e)
{
	$_SESSION['errorMessages'][] = $e;
	Header('Location: '.BASE_URL);
	exit();
}


if (isset($_FILES['mediafile']))
{
	$directory = APPLICATION_HOME.'/uploads/'.$user->getUsername();
	if (!is_dir($directory)) { mkdir($directory); }

	if (is_uploaded_file($_POST['mediafile']))
	{
		move_uploaded_file($_POST['mediafile']['name'],$directory.'/'.$_POST['mediafile']['name']);
	}
}
