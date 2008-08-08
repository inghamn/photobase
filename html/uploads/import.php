<?php
/**
 * @copyright Copyright (C) 2008 Cliff Ingham. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET name Directory name to import media from
 */
verifyUser();

$upload = $_SESSION['USER']->getUploadDirectory();

try
{
	$roll = $upload->import($_SESSION['USER']);
	Header('Location: '.BASE_URL.'/media?roll='.$roll->getId());
}
catch(Exception $e)
{
	$_SESSION['errorMessages'][] = $e;
	Header('Location: '.BASE_URL.'/uploads');
}
