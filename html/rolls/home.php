<?php
/**
 * @copyright Copyright (C) 2008 Cliff Ingham. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
$rollList = new RollList();
$rollList->find();

$template = new Template();
$template->blocks[] = new Block('rolls/rollList.inc',array('rollList'=>$rollList));
echo $template->render();