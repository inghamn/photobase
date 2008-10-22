<?php
/**
 * @copyright Copyright (C) 2008 Cliff Ingham. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Media $this->media
 */
$title = View::escape($this->media->getTitle());
if (isset($_SESSION['USER']) && $this->media->permitsEditingBy($_SESSION['USER']))
{
	$url = new URL(BASE_URL.'/media/edit.php');
	$url->media_id = $this->media->getId();
	$button = "<button type=\"button\" class=\"editSmall\" onclick=\"document.location.href='$url';\">Edit</button>";
}
else { $button = ''; }


$date = $this->media->getDate() ? $this->media->getDate('n/j/Y') : $this->media->getYear();
$description = View::escape($this->media->getDescription());
$address = array();
if ($this->media->getCity()) { $address[] = $this->media->getCity(); }
if ($this->media->getState()) { $address[] = $this->media->getState(); }
if ($this->media->getCountry()) { $address[] = $this->media->getCountry(); }
$address = View::escape(implode(', ',$address));

$notes = View::escape($this->media->getNotes());

echo "
<h1>$button$title</h1>
<div class=\"image medium\">
	<a href=\"{$this->media->getURL()}\">
		<img src=\"{$this->media->getURL('medium')}\" />
	</a>
</div>
<div>
	<div>$address</div>
	<p><strong>$date</strong>
		$description
	</p>
	<p>$notes</p>

</div>
";
