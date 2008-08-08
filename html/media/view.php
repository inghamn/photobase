<?php
/**
 * @copyright Copyright (C) 2008 Cliff Ingham. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET media_id
 */
$media = new Media($_GET['media_id']);

$template = new Template();
$template->blocks[] = new Block('media/view.inc',array('media'=>$media));
echo $template->render();
