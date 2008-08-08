<h1>Uploads</h1>
<ul>
<?php
/**
 * @copyright Copyright (C) 2008 Cliff Ingham. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
$list = new UserList();
$list->find();
foreach($list as $user)
{
	$c = count($user->getUploadDirectory());
	if ($c)
	{
		echo "
		<li>{$user->getUsername()}
			($c)
		</li>
		";
	}
}
?>
</ul>
