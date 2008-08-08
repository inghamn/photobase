<?php
/**
 * @copyright Copyright (C) 2008 Cliff Ingham. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param UserList $this->userList
 */
	if (userHasRole("Administrator"))
	{
		$addButton = "<a class=\"add button\" href=\"".BASE_URL."/users/addUser.php\">Add</a>";
	}
	else { $addButton = ""; }
?>
<div class="interfaceBox">
	<div class="titleBar"><?php echo $addButton; ?>Users</div>
	<table>
	<?php
		foreach($this->userList as $user)
		{
			if (userHasRole("Administrator"))
			{
				$editButton = "<a class=\"edit button\" href=\"".BASE_URL."/users/updateUser.php?id={$user->getId()}\">Edit</a>";
				$deleteButton = "<button type=\"button\" class=\"delete\" onclick=\"FRAMEWORK.deleteConfirmation('deleteUser.php?id={$user->getId()}');\">Delete</button>";
			}
			else
			{
				$editButton = "";
				$deleteButton = "";
			}

			$firstname = View::escape($user->getFirstname());
			$lastname = View::escape($user->getLastname());
			echo "
			<tr><td>{$editButton}{$deleteButton}</td>
				<td><a href=\"".BASE_URL."/users/viewUser.php?user_id={$user->getId()}\">{$user->getUsername()}</a></td>
				<td><a href=\"".BASE_URL."/users/viewUser.php?user_id={$user->getId()}\">$firstname $lastname</a></td>
				<td>{$user->getAuthenticationMethod()}</td>
				<td>
			";
					foreach($user->getRoles() as $role) { echo "$role "; }
			echo "</td></tr>";
		}
	?>
	</table>
</div>
