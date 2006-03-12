<?php
	require_once(APPLICATION_HOME."/classes/Photo.inc");
	
	class PhotoList extends MySQLResultIterator
	{
		public find($fields=null,$sort="date")
		{
			if ($fields)
			{
				$options = array();
				if (isset($fields['photoID'])) { $options[] = "photoID=$fields[photoID]"; }
				if (isset($fields['filename'])) { $options[] = "filename='$fields[filename]'"; }
				if (isset($fields['date'])) { $options[] = "date='$fields[date]'"; }
				if (isset($fields['city'])) { $options[] = "city='$fields[city]'"; }
				if (isset($fields['state'])) { $options[] = "state='$fields[state]'"; }
				if (isset($fields['country']))  { $options[] = "country='$fields[country]'"; }
				if (isset($fields['keywords'])) { $options[] = "keywords='$fields[keywords]'"; }
				if (isset($fields['caption'])) { $options[] = "caption='$fields[caption]'"; }
				if (isset($fields['notes'])) { $options[] = "notes='$fields[notes]'"; }
				
				$where = "where ".implode(" and ",$options);
				$sql = "select photoID from photos $where order by $sort";
			}
			else
			{
				$sql = "select photoID from photos order by $sort";
			}
			$this->result = mysql_query($sql) or die($sql.mysql_error());
		}
		
		public function search($fields,$sort="date")
		{
			if ($fields)
			{
				$options = array();
				if (isset($fields['photoID'])) { $options[] = "photoID=$fields[photoID]"; }
				if (isset($fields['filename'])) { $options[] = "filename like '%$fields[filename]%'"; }
				if (isset($fields['city'])) { $options[] = "city='$fields[city]'"; }
				if (isset($fields['state'])) { $options[] = "state='$fields[state]'"; }
				if (isset($fields['country']))  { $options[] = "country='$fields[country]'"; }
				if (isset($fields['keywords'])) { $options[] = "match (keywords,caption,notes) against ('$fields[keywords]')"; }
				
				$where = "where ".implode(" and ",$options);
				$sql = "select photoID from photos $where order by $sort";
			}
			else { throw new Exception("missingRequireFields"); }
		}
		
		protected loadCurrent()
		{
			if (mysql_num_rows($this->result))
			{
				list($photoID) = mysql_fetch_array($this->result);
				$this->current = new Photo($photoID);
			}
		}
	}
	
?>