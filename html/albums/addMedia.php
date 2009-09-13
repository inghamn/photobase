<?php
/**
 * @copyright Copyright 2009 Cliff Ingham
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param POST album_id
 * @param array media  An array of media_ids
 */
verifyUser();

try {
	$album = new Album($_POST['album_id']);
	$album->addMedia($POST['media']);
}
catch (Exception $e) {
	echo "Failure";
	$_SESSION['errorMessages'][] = $e;
}
