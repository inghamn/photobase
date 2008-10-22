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
	if (isset($_SESSION['USER']) && $media->permitsEditingBy($_SESSION['USER']))
	{
		$button = "<button type=\"button\" class=\"editSmall\" onclick=\"document.location.href='".BASE_URL."/media/edit.php?media_id={$media->getId()}';\">Edit</button>";
	}
	else { $button = ''; }

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
			$button
			$caption
		</span>
	</span>
	";
}
?>
</div>