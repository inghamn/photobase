<?php
/**
 * @copyright Copyright 2009 Cliff Ingham
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
verifyUser('Administrator');

$albumList = new AlbumList();
$albumList->find();

$template = new Template();
$template->blocks[] = new Block('albums/albumList.inc',array('albumList'=>$albumList));
echo $template->render();