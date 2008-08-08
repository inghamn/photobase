<div class="contactSheet">
<?php
/**
 * @copyright Copyright (C) 2009 City of Bloomington, Indiana. All rights reserved.
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

	echo "
	<span class=\"image thumbnail\">
		<a href=\"".BASE_URL."/media/view.php?media_id={$media->getId()}\">
			<img src=\"{$media->getURL('thumbnail')}\" />
		</a>
		<span class=\"caption\">
			$button
			{$media->getFilename()}
		</span>
	</span>
	";
}
?>
</div>