<div id="login">
	<div class="titleBar">Login</div>
	<form method="post" action="login.php">
	<fieldset><legend>Login</legend>
		<table>
		<tr><td><label for="username">User:</label></td>
			<td><input name="username" id="username" size="10" /></td></tr>
		<tr><td><label for="password">Pass:</label></td>
			<td><input type="password" name="password" id="password" size="10" /></td></tr>
		</table>
		<button type="submit" class="login">Login</button>
		<button type="button" class="cancel" onclick="document.location.href='<?php echo BASE_URL; ?>';">Cancel</button>
	</fieldset>
	</form>
</div>
<script type="text/javascript">
	document.getElementById('username').focus();
</script>