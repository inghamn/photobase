<?php
/**
 * @copyright Copyright (C) 2008 Cliff Ingham. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
$duplicates = MediaList::getDuplicateMD5s();
if (count($duplicates))
{
	echo "<table>";
	foreach($duplicates as $md5)
	{
		echo "<tr>";
		$list = new MediaList(array('md5'=>$md5));
		foreach($list as $i=>$media)
		{
			if ($i==0)
			{
				echo "
				<th><img src=\"{$media->getURL('thumbnail')}\" /></th>
				<td><ul>
				";
			}
			
			$deleteButton = '';
			if (userHasRole('Administrator'))
			{
				$url = new URL(BASE_URL.'/media/deleteMedia.php');
				$url->media_id = $media->getId();
				$url->return_url = $_SERVER['REQUEST_URI'];
				$deleteButton = "<button type=\"button\" class=\"delete\" onclick=\"FRAMEWORK.deleteConfirmation('$url');\">Delete</button>";
			}
			echo "
					<li><a href=\"".BASE_URL."/media/view.php?media_id={$media->getId()}\">
						{$media->getId()}</a>
						$deleteButton
					</li>
			";

		}
		echo "
					</ul>
				</td>
			</tr>
		";
	}
	echo "</table>";
}