<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
?>
<form method="post" action="<?php echo $_SERVER['SCRIPT_NAME']; ?>">
<fieldset><legend>New Password</legend>
	<p>Use this form if you want to change your password.</p>
	<table>
	<tr><td><label for="password">New Password</label></td>
		<td><input name="password" id="password" type="password" /></td></tr>
	<tr><td><label for="retypePassword">Retype New Password</label></td>
		<td><input name="retypePassword" id="retypePassword" type="password" /></td></tr>
	</table>
</fieldset>
<fieldset><legend>Personal Information</legend>
	<p>You can update any of your information down here.</p>
	<table>
	<tr><td><label for="user-firstname">Firstname</label></td>
		<td><input name="user[firstname]" id="user-firstname" value="<?php echo View::escape($_SESSION['USER']->getFirstname()); ?>" /></td></tr>
	<tr><td><label for="user-lastname">Lastname</label></td>
		<td><input name="user[lastname]" id="user-lastname" value="<?php echo View::escape($_SESSION['USER']->getLastname()); ?>" /></td></tr>
	<tr><td><label for="user-email">Email</label></td>
		<td><input name="user[email]" id="user-email" value="<?php echo View::escape($_SESSION['USER']->getEmail()); ?>" /></td></tr>
	</table>
</fieldset>
<fieldset><legend>Submit</legend>
	<button type="submit" class="save">Save</button>
	<button type="button" class="cancel" onclick="document.location.href='<?php echo BASE_URL; ?>';">Cancel</button>
</fieldset>
</form>