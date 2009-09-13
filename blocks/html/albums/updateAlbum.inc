<?php
/**
 * @copyright Copyright 2009 Cliff Ingham
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Album $this->album
 */
?>
<h1>Update Album</h1>
<form method="post" action="<?php echo $_SERVER['SCRIPT_NAME']; ?>">
<fieldset><legend>Album Info</legend>
	<input name="album_id" type="hidden" value="<?php echo $this->album->getId(); ?>" />

	<table>
	<tr><td><label for="album-name" class="required">Name</label></td>
		<td><input name="album[name]" id="album-name"
				value="<?php echo View::escape($this->album->getName()); ?>" />
		</td>
	</tr>
	</table>

	<button type="submit" class="submit">Submit</button>
	<a class="cancel button" href="<?php echo BASE_URL; ?>/albums">Cancel</a>
</fieldset>
</form>