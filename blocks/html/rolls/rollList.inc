<?php
/**
 * @copyright Copyright (C) 2008 Cliff Ingham. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
?>
<div class="interfaceBox">
	<h1>
		Rolls
	</h1>
	<ul><?php
			foreach($this->rollList as $roll)
			{
				$editButton = '';
				if (userHasRole('Administrator'))
				{
					$editButton = "<a class=\"edit button\" href=\"".BASE_URL."/rolls/updateRoll.php?id={$roll->getId()}\">Edit</a>";
				}
				
				$name = View::escape($roll->getName()); 
				echo "<li>$editButton $name</li>";
			}
		?>
	</ul>
</div>