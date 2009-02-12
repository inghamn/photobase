<?php
/**
 * @copyright 2009 Cliff Ingham
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET media_id
 * @param GET rotate (left,right)
 * @param GET return_url
 */
verifyUser();

$media = new Media($_GET['media_id']);

if ($media->permitsEditingBy($_SESSION['USER']))
{
	$media->rotate($_GET['rotate']);
}
header('Location: '.$_GET['return_url']);
