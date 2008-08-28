<?php
/**
 * @copyright Copyright (C) 2008 Cliff Ingham. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
verifyUser();

if (isset($_FILES['userfile']))
{
	$directory = $_SESSION['USER']->getUploadDirectory();
	$directory->add($_FILES['userfile']);
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
