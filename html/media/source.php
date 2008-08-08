<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET media_id
 * @param GET size
 * Displays the requested media at the request size.  If size is not given
 * it displays the medium size
 */
$media = new Media($_GET['media_id']);
$size = isset($_GET['size']) ? $_GET['size'] : '';

switch($size)
{
	case 'thumbnail':
		Header('Content-type: image/gif');
		$media->output('thumbnail');
		break;

	default:
		Header("Content-type: image/jpg");
		$media->output('medium');
}
