<div class="contactSheet">
<?php
/**
 * @copyright Copyright 2008-2009 Cliff Ingham
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param MediaList $this->mediaList
 */
if (count($this->mediaList))
{
	if (isset($_SESSION['USER']))
	{
		$url = new URL(BASE_URL.'/media/editPage.php');
		if (isset($_GET['page'])) { $url->page = $_GET['page']; }
		echo "
		<div>
			<button type=\"button\" onclick=\"document.location.href='$url';\">
				Edit this page
			</button>
		</div>
		";
	}
	foreach($this->mediaList as $media)
	{
		$caption = array();
		if ($media->getState()) { $caption[] = $media->getState(); }
		if ($media->getYear()) { $caption[] = $media->getYear(); }
		$caption = implode(', ',$caption);

		echo "
		<div class=\"image thumbnail\">
			<a href=\"".BASE_URL."/media/view.php?media_id={$media->getId()}\">
				<img src=\"{$media->getURL('thumbnail')}\" />
			</a>
			<div class=\"caption\">
				$caption
			</div>
			<div class=\"buttons\">
		";
				$buttons = new Block('media/editButtons.inc',array('media'=>$media));
				echo $buttons->render();
		echo "
			</div>
		</div>
		";
	}
}
else { echo "<p>No Photos Found.</p>"; }
?>
</div>
