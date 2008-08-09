<?php
/**
 * @copyright Copyright (C) 2008 Cliff Ingham. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
#--------------------------------------------------------------------
# Handle all the possible stuff people can pass in the URL
#--------------------------------------------------------------------
foreach($_REQUEST as $key=>$value)
{
	switch($key)
	{
		case 'roll_id':
			try
			{
				$roll = new Roll($_GET['roll_id']);
				$_SESSION['filters']['roll_id'] = $roll->getId();
			}
			catch (Exception $e) { $_SESSION['errorMessages'][] = $e; }
		break;

		case 'tag_id':
			try
			{
				$tag = new Tag($_GET['tag_id']);
				$_SESSION['filters']['tag_ids'][$tag->getId()] = $tag->getId();
			}
			catch (Exception $e) { $_SESSION['errorMessages'][] = $e; }
		break;

		case 'city':
		case 'state':
		case 'country':
			if ($value) { $_SESSION['filters'][$key] = $value; }
			else { unset($_SESSION['filters'][$key]); }
		break;

		case 'reset':
			if ($value) { unset($_SESSION['filters'][$value]); }
			else { $_SESSION['filters'] = array(); }
		break;
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
	$page = (isset($_GET['page']) && $_GET['page']) ? (int)$_GET['page'] : 0;
	if (!$pages->offsetExists($page)) { $page = 0; }

	$mediaList = new LimitIterator($list,$pages[$page],$pages->getPageSize());
}
else { $mediaList = $list; }



$template = new Template();
$template->blocks[] = new Block('media/currentFilters.inc');

$template->mediaList = $list;
$template->blocks[] = new Block('media/thumbnails.inc',array('mediaList'=>$mediaList));

if (isset($pages))
{
	$pageNavigation = new Block('pageNavigation.inc');
	$pageNavigation->page = $page;
	$pageNavigation->pages = $pages;
	$pageNavigation->url = new URL($_SERVER['SERVER_NAME'].$_SERVER['REQUEST_URI']);

	$template->blocks[] = $pageNavigation;
}
echo $template->render();
