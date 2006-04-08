<?php
	require_once(APPLICATION_HOME."/classes/MySQLResultIterator.inc");
	class UserList extends MySQLResultIterator
	{
		public function find($fields=null,$sort="lastname,firstname")
		{
			if ($fields)
			{
				$options = array();
				if (isset($fields['username'])) { $options[] = "username='$fields[username]'"; }
				if (isset($fields['firstname'])) { $options[] = "firstname='$fields[firstname]'"; }
				if (isset($fields['lastname'])) { $options[] = "lastname='$fields[lastname]'"; }

				$where = "where ".implode(" and ",$options);
				$sql = "select userID from users $where order by $sort";
			}
			else { $sql = "select userID from users order by $sort"; }

			$this->result = mysql_query($sql) or die($sql.mysql_error());
		}

		protected function loadCurrent()
		{
			if (mysql_num_rows($this->result))
			{
				list($userID) = mysql_fetch_array($this->result);
				$this->current = new User($userID);
			}
		}
	}
?>