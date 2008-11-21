<?php
/**
 * @copyright Copyright (C) 2008 Cliff Ingham. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
?>
<div class="menuBar">
	<ul>
		<li><a href="<?php echo BASE_URL; ?>">Home</a></li>
		<?php
			if (isset($_SESSION['USER']))
			{
				echo "
				<li><a href=\"".BASE_URL."/users/myInfo.php\">Edit Account</a></li>
				<li><a href=\"".BASE_URL."/uploads\">Uploads</a></li>
				<li><a href=\"".BASE_URL."/login/logout.php\">Logout</a></li>
				";
			}
			else { echo "<li><a href=\"".BASE_URL."/login\">Login</a></li>"; }
		?>
	</ul>
</div>
