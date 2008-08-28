<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param FILES userfile
 */
verifyUser();
$template = new Template('default','postlet');

if (isset($_FILES['userfile']))
{
	$directory = $_SESSION['USER']->getUploadDirectory();
	try { $directory->add($_FILES['userfile']); }
	catch (Exception $e)
	{
		if ($e->getMessage() == 'uploads/invalidFiletype')
		{
			$template->blocks[] = new Block('filetypeNotAllowed.inc');
		}
		else { $template->blocks[] = new Block('unknownError.inc'); }
	}
	$template->blocks[] = new Block('success.inc');
}
else
{
	$template->blocks[] = new Block('unknownError.inc');
}
echo $template->render();