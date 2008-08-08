<?php
/**
 * @copyright Copyright (C) 2008 Cliff Ingham. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET media_id
 */
verifyUser();

$media = new Media($_REQUEST['media_id']);

if (isset($_POST['media_id']))
{
	foreach($_POST['media'] as $field=>$value)
	{
		$set = 'set'.ucfirst($field);
		$media->$set($value);

		if (isset($_POST['date']))
		{
			$media->setDate("$_POST[date] $_POST[time]");
		}
	}

	try
	{
		$media->save();
		Header('Location: '.BASE_URL);
		exit();
	}
	catch (Exception $e) { $_SESSION['errorMessages'][] = $e; }
}

$template = new Template();
$template->blocks[] = new Block('media/view.inc',array('media'=>$media));
$template->blocks[] = new Block('media/editForm.inc',array('media'=>$media));
echo $template->render();
