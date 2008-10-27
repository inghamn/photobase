<?php
/**
 * @copyright Copyright (C) 2008 Cliff Ingham. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @param Roll $this->roll
 */
?>
<h1>Update Roll</h1>
<form method="post" action="<?php echo $_SERVER['SCRIPT_NAME']; ?>">
<fieldset><legend>Roll Info</legend>
	<input name="id" type="hidden" value="<?php echo $this->roll->getId(); ?>" />
	<table>

	<tr><td><label for="roll-name" class="required">Name</label></td>
		<td><input name="roll[name]" id="roll-name" value="<?php echo View::escape($this->roll->getName()); ?>" /></td></tr>
		
	<tr><td><label for="roll-date" class="required">Date</label></td>
		<td><input name="roll[date]" id="roll-date" value="<?php echo $this->roll->getDate('Y-m-d'); ?>" /></td></tr>
		
	</table>

	<button type="submit" class="submit">Submit</button>
	<a class="cancel button" href="<?php echo BASE_URL; ?>/rolls">Cancel</a>
</fieldset>
</form>