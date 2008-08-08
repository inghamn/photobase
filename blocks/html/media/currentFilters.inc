<?php
/**
 * @copyright Copyright (C) 2008 Cliff Ingham. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
if (isset($_SESSION['filters']) && count($_SESSION['filters']))
{
	echo "
	<div class=\"interfaceBox\">
		<h1>
			<a class=\"reset button\" href=\"".BASE_URL."/media?reset\">Reset</a>
			Filters
		</h1>
		<ul>
	";
	foreach($_SESSION['filters'] as $filter=>$value)
	{
		switch($filter)
		{
			case 'tag_ids':
				$tags = array();
				foreach($value as $id)
				{
					$tag = new Tag($id);
					$tags[] = View::escape($tag);
				}
				$label = 'Tags';
				$value = implode(',',$tags);
			break;

			case 'roll_id':
				$roll = new Roll($value);
				$value = View::escape($roll->getName());
				$label = 'Roll';
			break;

			default:
				$label = ucfirst($filter);
				$value = View::escape($value);
		}

		echo "
		<li><a class=\"delete button\" href=\"".BASE_URL."/media?reset=$filter\">Delete</a>
			$label:$value
		</li>
		";
	}
	echo "
		</ul>
	</div>
	";
}
