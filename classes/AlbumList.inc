<?php
/**
 * @copyright 2009 Cliff Ingham
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham
 */
class AlbumList extends PDOResultIterator
{
	public function __construct($fields=null)
	{
		$this->select = 'select distinct a.id as id from albums a';
		if (is_array($fields)) $this->find($fields);
	}

	public function find($fields=null,$sort='name',$limit=null,$groupBy=null)
	{
		$this->sort = $sort;
		$this->limit = $limit;
		$this->groupBy = $groupBy;
		$this->joins = '';

		$options = array();
		if (isset($fields['id'])) { $options[] = "a.id='$fields[id]'"; }
		if (isset($fields['name'])) { $options[] = "a.name='$fields[name]'"; }


		# Finding on fields from other tables required joining those tables.
		# You can add fields from other tables to $options by adding the join SQL
		# to $this->joins here

		$this->populateList($options);
	}

	protected function loadResult($key) { return new Album($this->list[$key]); }
}
