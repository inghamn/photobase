<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET image
 */
verifyUser();

$size = 'thumbnail';
$directory = APPLICATION_HOME.'/uploads/'.$_SESSION['USER']->getUsername();
	
preg_match('/(^.*)\.([^\.]+)$/',$_GET['image'],$matches);
$filename = $matches[1];

$mediaSizes = Media::getSizes();
$ext = $mediaSizes[$size]['ext'];
	
if (!is_file("$directory/$size/$filename.$ext"))
{
	Media::resize($directory.'/'.$_GET['image'],$size);
}

Header("Content-type: image/gif");
readfile("$directory/$size/$filename.$ext");
