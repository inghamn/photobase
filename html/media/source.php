<?php
/**
 * @copyright Copyright (C) 2008 Cliff Ingham. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET media_id
 * @param GET size
 * Displays the requested media at the request size.  If size is not given
 * it displays the medium size
 */
$media = new Media($_GET['media_id']);
$size = isset($_GET['size']) ? $_GET['size'] : '';

foreach(Media::getSizes() as $knownSize=>$sizeInfo)
{
	if ($size == $knownSize)
	{
		$extensions = Media::getExtensions();
		Header('Content-type: '.$extensions[$sizeInfo['ext']]['mime_type']);
		$media->output($size);
		exit();
	}
}

# If we could find the size they asked for, just show the medium size
Header("Content-type: image/jpg");
$media->output('medium');
