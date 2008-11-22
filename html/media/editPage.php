<?php
/**
 * @copyright Copyright (C) 2008 Cliff Ingham. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param REQUEST page
 *
 * This screen is used to let the user edit a page of photos all at once
 */
verifyUser();

$page = (isset($_REQUEST['page']) && $_REQUEST['page']) ? (int)$_REQUEST['page'] : 0;

if (isset($_POST['media']))
{
	foreach($_POST['media'] as $id=>$post)
	{
		try
		{
			$media = new Media($id);
			foreach($post as $field=>$value)
			{
				$set = 'set'.ucfirst($field);
				$media->$set($value);
			}
			$media->save();
			Header('Location: '.BASE_URL.'?page=$page');
			exit();
		}
		catch(Exception $e)
		{
			$_SESSION['errorMessages'][] = $e;
		}
	}
}

#--------------------------------------------------------------------
# Load the media and start displaying the page
#--------------------------------------------------------------------
$list = new MediaList();
$list->find($_SESSION['filters']);

# If we've got a lot of photos, split them up into seperate pages
if (count($list) > 12)
{
	$pages = new Paginator($list,12);

	# Make sure we're asking for a page that actually exists
	if (!$pages->offsetExists($page)) { $page = 0; }

	$mediaList = new LimitIterator($list,$pages[$page],$pages->getPageSize());
}
else { $mediaList = $list; }

$template = new Template();
$template->mediaList = $list;

$form = new Block('media/editPageForm.inc');
$form->mediaList = $mediaList;
if (isset($page)) { $form->page = $page; }
$template->blocks[] = $form;

echo $template->render();
