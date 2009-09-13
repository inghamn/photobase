<?php
/**
 * @copyright Copyright 2009 Cliff Ingham
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET album_id
 */
verifyUser('Administrator');

$album = new Album($_REQUEST['album_id']);
if (isset($_POST['album']))
{
	$album->setName($_POST['album']['name']);

	try
	{
		$album->save();
		Header('Location: '.BASE_URL.'/albums');
		exit();
	}
	catch (Exception $e) { $_SESSION['errorMessages'][] = $e; }
}

$template = new Template();
$template->blocks[] = new Block('albums/updateAlbumForm.inc',array('album'=>$album));
echo $template->render();