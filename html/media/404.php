<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
if (preg_match('|/([a-z]+)/([0-9]+)\.[a-z]{3}$|',$_SERVER['REQUEST_URI'],$matches))
{
	$_GET['size'] = $matches[1];
	$_GET['media_id'] = $matches[2];
	
	try { $media = new Media($_GET['media_id']); }
	catch (Exception $e) { $_SESSION['errorMessages'][] = $e; }
	
	include APPLICATION_HOME.'/html/media/source.php';
}
else { $_SESSION['errorMessages'][] = new Exception('media/unknownMedia'); }

Header('http/1.1 404 Not Found');
Header('Status: 404 Not Found');
$template = new Template();
echo $template->render();
