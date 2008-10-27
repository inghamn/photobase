<?php
/**
 * @copyright Copyright (C) 2008 Cliff Ingham. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
verifyUser('Administrator');

$roll = new Roll($_REQUEST['id']);
if (isset($_POST['roll']))
{
	foreach($_POST['roll'] as $field=>$value)
	{
		$set = 'set'.ucfirst($field);
		$roll->$set($value);
	}

	try
	{
		$roll->save();
		Header('Location: home.php');
		exit();
	}
	catch (Exception $e) { $_SESSION['errorMessages'][] = $e; }
}

$template = new Template();
$template->blocks[] = new Block('rolls/updateRollForm.inc',array('roll'=>$roll));
echo $template->render();