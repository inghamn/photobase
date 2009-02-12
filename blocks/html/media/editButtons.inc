<?php
/**
 * @copyright 2009 City of Bloomington, Indiana
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Media $this->media
 */
if (isset($_SESSION['USER']) && $this->media->permitsEditingBy($_SESSION['USER']))
{
	$url = new URL(BASE_URL.'/media/edit.php');
	$url->media_id = $this->media->getId();
	$url->return_url = $_SERVER['REQUEST_URI'];
	echo "
	<button type=\"button\" class=\"edit\" onclick=\"document.location.href='$url';\">
		Edit Photo
	</button>
	";

	$url = new URL(BASE_URL.'/media/modify.php');
	$url->media_id = $this->media->getId();
	$url->rotate = 'left';
	$url->return_url = $_SERVER['REQUEST_URI'];
	echo "
	<button type=\"button\" class=\"rotateLeft\" onclick=\"document.location.href='$url';\">
		Rotate Left
	</button>
	";

	$url->rotate = 'right';
	echo "
	<button type=\"button\" class=\"rotateLeft\" onclick=\"document.location.href='$url';\">
		Rotate Right
	</button>
	";
}
