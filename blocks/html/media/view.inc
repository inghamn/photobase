<?php
/**
 * @copyright Copyright (C) 2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Media $this->media
 */
$title = View::escape($this->media->getTitle());
if (isset($_SESSION['USER']) && $this->media->permitsEditingBy($_SESSION['USER']))
{
	$button = "<button type=\"button\" class=\"editSmall\" onclick=\"document.location.href='".BASE_URL."/media/edit.php?media_id={$this->media->getId()}';\">Edit</button>";
}
else { $button = ''; }

echo "
<h1>$button$title</h1>
<div class=\"image medium\">
	<a href=\"{$this->media->getURL()}\">
		<img src=\"{$this->media->getURL('medium')}\" />
	</a>
</div>
";
