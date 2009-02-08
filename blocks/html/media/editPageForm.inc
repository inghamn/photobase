<?php
/**
 * @copyright Copyright (C) 2008 Cliff Ingham. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param MediaList $this->mediaList
 * @param int $this->page
 */
?>
<form method="post" action="editPage.php">
<fieldset><legend>Edit Photos</legend>
	<table>
	<tr><th></th>
		<th>Date</th>
		<th>City</th>
		<th>State</th>
		<th>Country</th>
		<th>Tags</th>
	</tr>
<?php
foreach($this->mediaList as $media)
{
	$tags = implode(' ',$media->getTags());
	$date = $media->getDate('Y-m-d');
	$city = View::escape($media->getCity());
	$state = View::escape($media->getState());
	$country = View::escape($media->getCountry());
	$description = View::escape($media->getDescription());

	echo "
	<tr><th rowspan=\"2\"><img src=\"{$media->getURL('icon')}\" /></th>
		<td><input name=\"media[{$media->getId()}][date]\" size=\"10\" maxlength=\"10\" value=\"$date\" /></td>
		<td><input name=\"media[{$media->getId()}][city]\" value=\"$city\" size=\"10\" /></td>
		<td><input name=\"media[{$media->getId()}][state]\" size=\"3\" value=\"$state\" /></td>
		<td><input name=\"media[{$media->getId()}][country]\" size=\"7\" value=\"$country\"/></td>
		<td><input name=\"media[{$media->getId()}][tags]\" value=\"$tags\" /></td>
	</tr>
	<tr><td colspan=\"5\">
			<textarea name=\"media[{$media->getId()}][description\" rows=\"2\" cols=\"60\">$description</textarea>
		</td>
	</tr>
	";
}
?>
	</table>
</fieldset>

<fieldset><legend>Save</legend>
	<?php
		$return_url = new URL(BASE_URL);
		if (isset($this->page))
		{
			echo "<input name=\"page\" type=\"hidden\" value=\"{$this->page}\" />";
			$return_url->page = $this->page;
		}
	?>
	<button type="submit" class="save">Save</button>
	<button type="button" class="cancel" onclick="document.location.href='<?php echo $return_url; ?>';">Cancel</button>
</fieldset>
</form>