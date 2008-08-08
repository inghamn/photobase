<?php
/**
 * @copyright Copyright (C) 2008 Cliff Ingham. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param POST file
 * @param POST username (These are optional, if there's already a logged in SESSION)
 * @param POST password (These are optional, if there's already a logged in SESSION)
 * @param POST return_url (Optional url to redirect to when done)
 */
if (!isset($_SESSION['USER']))
{
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
}

$uploads = new Upload($_SESSION['USER']);
$uploads->addFile($_POST['file']):

if (isset($_POST['return_url']))
{
	Header("Location: $_POST[return_url]");
}
