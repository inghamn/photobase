<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
verifyUser('Administrator');

$userList = new UserList();
$userList->find();

$template = new Template();
$template->blocks[] = new Block('users/userList.inc',array('userList'=>$userList));

echo $template->render();
