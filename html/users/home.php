<?php
	verifyUser("Administrator");
	include(APPLICATION_HOME."/includes/xhtmlHeader.inc");
	include(APPLICATION_HOME."/includes/banner.inc");
	include(APPLICATION_HOME."/includes/controls.inc");
	include(APPLICATION_HOME."/includes/categories.inc");
?>
<div id="mainContent">
	<div class="interfaceBox">
		<div class="titleBar">
			<button type="button" class="addSmall" onclick="document.location.href='addUserForm.php';">Add</button>
			Users</div>
		<table>
		<?php
			require_once(APPLICATION_HOME."/classes/UserList.inc");
			$userList = new UserList();
			$userList->find();
			foreach($userList as $user)
			{
				$roles = implode(", ",$user->getRoles());
				echo "
				<tr><td><button type=\"button\" class=\"editSmall\" onclick=\"document.location.href='updateUserForm.php?userID={$user->getUserID()}';\">Edit</button>
						<button type=\"button\" class=\"deleteSmall\" onclick=\"deleteConfirmation('deleteUser.php?userID={$user->getUserID()}');\">Delete</button></td>
					<td>{$user->getUsername()}</td>
					<td>{$user->getFirstname()} {$user->getLastname()}</td>
					<td>$roles</td>
				</tr>
				";
			}
		?>
		</table>
	</div>
</div>
<?php include(APPLICATION_HOME."/includes/xhtmlFooter.inc"); ?>