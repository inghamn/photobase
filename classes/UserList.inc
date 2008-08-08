<?php
/**
 * @copyright Copyright (C) 2006,2007 Cliff Ingham. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
class UserList extends PDOResultIterator
{
	public function __construct($fields=null)
	{
		$this->select = "select distinct users.id from users";
		if (is_array($fields)) { $this->find($fields); }
	}


	public function find($fields=null,$sort="username",$limit=null,$groupBy=null)
	{
		$this->sort = $sort;
		$this->limit = $limit;
		$this->groupBy = $groupBy;

		if (is_array($fields))
		{
			foreach($fields as $key=>$value)
			{
				if (!is_array($value) && !is_object($value)) { $fields[$key] = addslashes($value); }
			}
		}

		$options = array();
		if (isset($fields['id'])) { $options[] = "id='$fields[id]'"; }
		if (isset($fields['username'])) { $options[] = "username='$fields[username]'"; }
		if (isset($fields['password'])) { $options[] = "password='$fields[password]'"; }
		if (isset($fields['authenticationMethod'])) { $options[] = "authenticationMethod='$fields[authenticationMethod]'"; }
		if (isset($fields['firstname'])) { $options[] = "firstname='$fields[firstname]'"; }
		if (isset($fields['lastname'])) { $options[] = "lastname='$fields[lastname]'"; }
		if (isset($fields['email'])) { $options[] = "email='$fields[email]'"; }

		# To search on Role, you have to join the userRoles table
		if (isset($fields['role']))
		{
			$this->joins = "left join user_roles on users.id=user_id left join roles on role_id=roles.id";
			$options[] = "role='$fields[role]'";
		}

		$this->populateList($options);
	}

	public function search(array $fields,$sort="username")
	{
		$this->sort = $sort;

		$options = array();
		if (isset($fields['id'])) { $options[] = "id='$fields[id]'"; }
		if (isset($fields['username'])) { $options[] = "username='$fields[username]'"; }
		if (isset($fields['password'])) { $options[] = "password='$fields[password]'"; }
		if (isset($fields['authenticationMethod'])) { $options[] = "authenticationMethod='$fields[authenticationMethod]'"; }
		if (isset($fields['firstname'])) { $options[] = "firstname like '$fields[firstname]%'"; }
		if (isset($fields['lastname'])) { $options[] = "lastname like '$fields[lastname]%'"; }
		if (isset($fields['email'])) { $options[] = "email='$fields[email]'"; }

		# To search on Role, you have to join the userRoles table
		if (isset($fields['role']))
		{
			$this->joins = "left join user_roles on users.id=user_id left join roles on role_id=roles.id";
			$options[] = "role='$fields[role]'";
		}

		$this->populateList($options);
	}

	protected function loadResult($key) { return new User($this->list[$key]); }
}
