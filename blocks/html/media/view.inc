<?php
/**
 * @copyright 2008-2008 Cliff Ingham
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Media $this->media
 */
$title = View::escape($this->media->getTitle());

$date = $this->media->getDate() ? $this->media->getDate('n/j/Y') : $this->media->getYear();
$description = View::escape($this->media->getDescription());
$address = array();
if ($this->media->getCity()) { $address[] = $this->media->getCity(); }
if ($this->media->getState()) { $address[] = $this->media->getState(); }
if ($this->media->getCountry()) { $address[] = $this->media->getCountry(); }
$address = View::escape(implode(', ',$address));

$notes = View::escape($this->media->getNotes());

echo "
<h1>$title</h1>
<div>
";
	$buttons = new Block('media/editButtons.inc',array('media'=>$this->media));
	echo $buttons->render();
echo "
</div>
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
