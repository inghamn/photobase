<?php
/**
 * @copyright Copyright (C) 2008 Cliff Ingham. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param GET media_id
 * @param GET return_url
 */
verifyUser('Administrator');

$media = new Media($_GET['media_id']);
$media->delete();

Header("Location: $_GET[return_url]");