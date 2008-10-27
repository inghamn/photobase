<div class="contactSheet">
<?php
/**
 * @copyright Copyright (C) 2008 Cliff Ingham. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param MediaList $this->mediaList
 */
foreach($this->mediaList as $media)
{
	$editButton = '';
	if (isset($_SESSION['USER']) && $media->permitsEditingBy($_SESSION['USER']))
	{
		$url = new URL(BASE_URL.'/media/edit.php');
		$url->media_id = $media->getId();
		$url->return_url = $_SERVER['REQUEST_URI'];
		$editButton = "<button type=\"button\" class=\"edit\" onclick=\"document.location.href='$url';\">Edit Photo</button>";
	}

	$caption = array();
	if ($media->getState()) { $caption[] = $media->getState(); }
	if ($media->getYear()) { $caption[] = $media->getYear(); }
	$caption = implode(', ',$caption);

	echo "
	<span class=\"image thumbnail\">
		<a href=\"".BASE_URL."/media/view.php?media_id={$media->getId()}\">
			<img src=\"{$media->getURL('thumbnail')}\" />
		</a>
		<span class=\"caption\">
			$editButton
			$caption
		</span>
	</span>
	";
}
?>
</div>