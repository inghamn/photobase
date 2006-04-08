<?php
	verifyUser("Administrator");
	include(APPLICATION_HOME."/includes/xhtmlHeader.inc");
	include(APPLICATION_HOME."/includes/banner.inc");
	include(APPLICATION_HOME."/includes/controls.inc");
	include(APPLICATION_HOME."/includes/categories.inc");
?>
<div id="mainContent">
	<h1>Add a User</h1>

	<form method="post" action="addUser.php">
	<fieldset><legend>Required Info</legend>
		<table>
		<tr><td><label for="username">Username</label></td>
			<td><input name="username" id="username" /></td></tr>
		<tr><td><label for="firstname">Firstname</label></td>
			<td><input name="firstname" id="firstname" /></td></tr>
		<tr><td><label for="lastname">Lastname</label></td>
			<td><input name="lastname" id="lastname" /></td></tr>
		<tr><td><label for="roles">Roles</label></td>
			<td><select name="roles[]" id="roles" multiple="multiple" size="2">
					<option>Administrator</option>
					<option>Editor</option>
				</select>
			</td>
		</tr>
		<tr><td><label for="password">Password</label></td>
			<td><input name="password" id="password" type="password" /></td></tr>
		</table>

		<button type="submit" class="submit">Submit</button>
		<button type="button" class="cancel" onclick="document.location.href='home.php';">Cancel</button>
	</fieldset>
	</form>
</div>
<?php include(APPLICATION_HOME."/includes/xhtmlFooter.inc"); ?>