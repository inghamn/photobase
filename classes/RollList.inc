<?php
/**
 * @copyright Copyright (C) 2008 Cliff Ingham. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
class RollList extends PDOResultIterator
{

	public function __construct($fields=null)
	{
		$this->select = 'select rolls.id as id from rolls';
		if (is_array($fields)) $this->find($fields);
	}
	

	public function find($fields=null,$sort='id',$limit=null,$groupBy=null)
	{
		$this->sort = $sort;
		$this->limit = $limit;
		$this->groupBy = $groupBy;
		$this->joins = '';

		$options = array();
		if (isset($fields['id'])) { $options[] = "id='$fields[id]'"; }
		if (isset($fields['name'])) { $options[] = "name='$fields[name]'"; }
		if (isset($fields['date'])) { $options[] = "date='$fields[date]'"; }
		if (isset($fields['user_id'])) { $options[] = "user_id='$fields[user_id]'"; }


		# Finding on fields from other tables required joining those tables.
		# You can add fields from other tables to $options by adding the join SQL
		# to $this->joins here

		$this->populateList($options);
	}
	

	protected function loadResult($key) { return new Roll($this->list[$key]); }
}
