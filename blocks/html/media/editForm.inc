<?php
/**
 * @copyright Copyright (C) 2008 Cliff Ingham. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Media $this->media
 */
?>
<form method="post" action="<?php echo $_SERVER['SCRIPT_NAME']; ?>">
<fieldset><legend>Media</legend>
	<input name="media_id" type="hidden" value="<?php echo $this->media->getId(); ?>" />
	<table>
	<tr><td><label for="media-title">Title</label></td>
		<td><input name="media[title]" id="media-title" value="<?php echo htmlspecialchars($this->media->getTitle(),ENT_QUOTES); ?>" /></td></tr>
	<tr><td colspan="2">
			<div><label for="media-description">Description</label></div>
			<textarea name="media[description]" id="media-description" rows="3" cols="60"><?php echo htmlspecialchars($this->media->getDescription()); ?></textarea>
	</td></tr>
	<tr><td><label for="media-tags">Tags</label></td>
		<td><input name="media[tags]" id="media-tags" value="<?php echo implode(' ',$this->media->getTags()); ?>" /></td></tr>
	<tr><td><label for="date">Date</label></td>
		<td><input name="date" id="date" size="10" maxlength="10" value="<?php echo $this->media->getDate('n/j/Y'); ?>" />
			<input name="time" id="time" size="7" maxlength="7" value="<?php echo $this->media->getDate('g:ia'); ?>" />
		</td>
	</tr>
	<tr><td><label for="media-city">city</label></td>
		<td><input name="media[city]" id="media-city" value="<?php echo $this->media->getCity(); ?>" /></td></tr>

	<tr><td><label for="media-state">state</label></td>
		<td><input name="media[state]" id="media-state" value="<?php echo $this->media->getState(); ?>" /></td></tr>

	<tr><td><label for="media-country">country</label></td>
		<td><input name="media[country]" id="media-country" value="<?php echo $this->media->getCountry(); ?>" /></td></tr>

	<tr><td><label for="media-notes">notes</label></td>
		<td><input name="media[notes]" id="media-notes" value="<?php echo $this->media->getNotes(); ?>" /></td></tr>
	</table>

	<button type="submit" class="save">Save</button>
	<button type="button" class="cancel" onclick="document.location.href='<?php echo BASE_URL; ?>/media/view.php?media_id=<?php echo $this->media->getId(); ?>';">Cancel</button>
</fieldset>
</form>
