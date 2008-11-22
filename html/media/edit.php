<?php
/**
 * @copyright Copyright (C) 2008 Cliff Ingham. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param REQUEST media_id
 * @param REQUEST return_url
 */
verifyUser();

$media = new Media($_REQUEST['media_id']);

if (isset($_POST['media_id']))
{
	foreach($_POST['media'] as $field=>$value)
	{
		$set = 'set'.ucfirst($field);
		$media->$set($value);
	}

	try
	{
		$media->save();
		Header("Location: $_REQUEST[return_url]");
		exit();
	}
	catch (Exception $e) { $_SESSION['errorMessages'][] = $e; }
}

$template = new Template();
$template->blocks[] = new Block('media/view.inc',array('media'=>$media));

$form = new Block('media/editForm.inc');
$form->media = $media;
$form->return_url = $_REQUEST['return_url'];
$template->blocks[] = $form;

echo $template->render();
