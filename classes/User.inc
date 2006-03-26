<?php
	class User
	{
		private $userID;
		private $username;
		private $password;
		private $firstname;
		private $lastname;
		private $roles = array();
		
		public function __construct($id=null)
		{
			if ($id)
			{
				if (is_numeric($id)) { $sql = "select * from users where userID=$id"; }
				else { $sql = "select * from users where username='$id'"; }
				$result = mysql_query($sql) or die($sql.mysql_error());
				if (mysql_num_rows($result))
				{
					$user = mysql_fetch_array($result);
					$this->userID = $user['userID'];
					$this->username = $user['username'];
					$this->firstname = $user['firstname'];
					$this->lastname = $user['lastname'];
					
					$this->loadRoles();
				}
				else { throw new Exception($sql); }
			}
		}
		
		
		
		public function addRole($role) { if(!in_array($role,$this->roles)) { $this->roles[] = $role; } }
		public function deleteRole($role) { foreach($this->roles as $i=>$r) { if ($r == $role) unset($this->roles[$i]); } }
		


		public function authenticate($password)
		{
			$sql = "select userID from users where username='{$this->getUsername()}' and password=md5('$password')";
			$result = mysql_query($sql) or die($sql.mysql_error());
			if (mysql_num_rows($result)) { return true; }
			else { return false; }
		}

		public function startNewSession()
		{
			session_destroy();
			session_start();

			$_SESSION['USER'] = $this;
			$_SESSION['IP_ADDRESS'] = $_SERVER['REMOTE_ADDR'];
		}

		public function save()
		{
			if ($this->getUserID()) { $this->update(); }
			else { $this->insert(); }
			
			if ($this->password) { $this->savePassword(); }
			$this->saveRoles();
		}

		public function delete()
		{
			$sql = "delete from users where userID={$this->userID}";
			mysql_query($sql) or die($sql.mysql_error());
			
			$sql = "delete from userRoles where userID={$this->userID}";
			mysql_query($sql) or die($sql.mysql_error());
		}

		public function savePassword()
		{
			$sql = "update users set password=md5('$this->password') where userID={$this->userID}";
			mysql_query($sql) or die($sql.mysql_error());
		}
		
		private function update()
		{
			$sql = "update users set username='{$this->username}',firstname='{$this->firstname}',lastname='{$this->lastname}' where userID={$this->userID}";
			mysql_query($sql) or die($sql.mysql_error());
		}
		
		private function insert()
		{
			$sql = "update users set username='{$this->username}',firstname='{$this->firstname}',lastname='{$this->lastname}'";
			mysql_query($sql) or die($sql.mysql_error());
			
			$this->userID = mysql_insert_id();
		}
		
		private function saveRoles()
		{
			$sql = "delete from userRoles where userID={$this->userID}";
			mysql_query($sql) or die($sql.mysql_error());
			
			foreach($this->roles as $role)
			{
				$sql = "insert userRoles values({$this->userID},'$role')";
				mysql_query($sql) or die($sql.mysql_error());
			}
		}

		private function loadRoles()
		{
			$this->roles = array();
			$sql = "select role from userRoles where userID={$this->userID}";
			$result = mysql_query($sql) or die($sql.mysql_error());
			while(list($role) = mysql_fetch_array($result)) { $this->roles[] = $role; }
		}



		public function getUserID() { return $this->userID; }
		public function getUsername() { return $this->username; }
		public function getFirstname() { return $this->firstname; }
		public function getLastname() { return $this->lastname; }
		public function getRoles() { return $this->roles; }
		public function getPassword() { return $this->password; }


		public function setUserID($userID) { $this->userID = $userID; }
		public function setFirstname($string) { $this->firstname = sanitizeString($string); }
		public function setLastname($string) { $this->lastname = sanitizeString($string); }
		public function setUsername($username)
		{
			$username = sanitizeString($username);
			if ($username) { $this->username = $username; }
		}
		public function setPassword($string) { $this->password = $string; }
	}
?>