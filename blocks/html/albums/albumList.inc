<?php
/**
 * @copyright Copyright 2009 Cliff Ingham
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param AlbumList $this->albumList
 */
?>
<div class="interfaceBox">
	<h1>Albums</h1>
	<ul><?php
			foreach($this->albumList as $album)
			{
				$editButton = '';
				if (userHasRole('Administrator'))
				{
					$editButton = "<a class=\"edit button\" href=\"".BASE_URL."/albums/updateAlbum.php?album_id={$album->getId()}\">Edit</a>";
				}

				$name = View::escape($album->getName());
				echo "<li>$editButton $name</li>";
			}
		?>
	</ul>
</div>