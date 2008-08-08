<?php
/**
 * @copyright Copyright (C) 2008 Cliff Ingham. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
if (!isset($_SESSION['USER']))
{
	try
	{
		if (isset($_POST['username']) && isset($_POST['password']))
		{
			$user = new User($_POST['username']);

			if ($user->authenticate($_POST['password'])) { $user->startNewSession(); }
			else { throw new Exception('wrongPassword'); }
		}
		else { throw new Exception('noAccessAllowed'); }
	}
	catch (Exception $e)
	{
		$_SESSION['errorMessages'][] = $e;
		Header('Location: '.BASE_URL);
		exit();
	}
}

if (isset($_FILES['mediafile']))
{
	$directory = $_SESSION['USER']->getUploadDirectory();
	$directory->add($_FILES['mediafile']);
}

if (isset($_POST['roll_name']) && $_POST['roll_name'])
{
	try
	{
		$roll = $_SESSION['USER']->getUploadDirectory()->import($_POST['roll_name']);
		Header('Location: '.BASE_URL.'/media?roll='.$roll->getId());
	}
	catch(Exception $e) { $_SESSION['errorMessages'][] = $e; }
}

$template = new Template();
$template->blocks[] = new Block('uploads/uploadForm.inc');
$template->blocks[] = new Block('uploads/userUploads.inc',array('user'=>$_SESSION['USER']));
echo $template->render();
