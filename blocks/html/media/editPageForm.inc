<?php
/**
 * @copyright 2008-2009 Cliff Ingham
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
		<th><button type="button" onclick="fillDown('date');">Date</button></th>
		<th><button type="button" onclick="fillDown('cty');">City</button></th>
		<th><button type="button" onclick="fillDown('state');">State</button></th>
		<th><button type="button" onclick="fillDown('country');">Country</button></th>
		<th><button type="button" onclick="fillDown('tags');">Tags</button></th>
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
		<td><input name=\"media[{$media->getId()}][date]\" id=\"date_{$media->getId()}\" size=\"10\" maxlength=\"10\" value=\"$date\" /></td>
		<td><input name=\"media[{$media->getId()}][city]\" id=\"city_{$media->getId()}\" value=\"$city\" size=\"10\" /></td>
		<td><input name=\"media[{$media->getId()}][state]\" id=\"state_{$media->getId()}\" size=\"3\" value=\"$state\" /></td>
		<td><input name=\"media[{$media->getId()}][country]\" id=\"country_{$media->getId()}\" size=\"7\" value=\"$country\"/></td>
		<td><input name=\"media[{$media->getId()}][tags]\" id=\"tags_{$media->getId()}\" value=\"$tags\" /></td>
	</tr>
	<tr><td colspan=\"5\">
			<textarea name=\"media[{$media->getId()}][description]\" rows=\"2\" cols=\"60\">$description</textarea>
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
<script type="text/javascript">
	<?php
		$media_ids = array();
		foreach ($this->mediaList as $media) {
			$media_ids[] = $media->getId();
		}
		$media_ids = implode(',',$media_ids);
		echo "var media_ids = [$media_ids];";
	?>
	function fillDown(field) {
		fieldname = field + '_' + media_ids[0];
		targetValue = document.getElementById(fieldname).value;
		
		for (i=1; i<media_ids.length; i++) {
			document.getElementById(field + '_' + media_ids[i]).value = targetValue;
		}
	}
</script>