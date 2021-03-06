<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
*/
/*
	Roles are really just an attribute array for users.  For now, I'm not loading them in as objects.
*/
class RoleList extends PDOResultIterator
{
	public function find($fields=null,$sort='role',$limit=null,$groupBy=null)
	{
		$PDO = Database::getConnection();

		if (is_array($fields))
		{
			foreach($fields as $key=>$value)
			{
				if (!is_array($value) && !is_object($value)) { $fields[$key] = addslashes($value); }
			}
		}

		$options = array();
		if (isset($fields['role'])) { $options[] = "role='$fields[role]'"; }

		if (count($options)) { $where = " where ".implode(" and ",$options); } else { $where = ""; }
		$sql = "select role from roles $where order by $sort";

		foreach($PDO->query($sql) as $row) { $this->list[] = $row['role']; }
	}


	protected function loadResult($key) { return $this->list[$key]; }
}
