<?php
/**
 * @copyright Copyright (C) 2007-2008 Cliff Ingham. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
class MediaList extends PDOResultIterator
{
	public function __construct($fields=null)
	{
		$this->select = 'select m.id as id from media m';
		if (is_array($fields)) $this->find($fields);
	}

	public function find($fields=null,$sort='m.date',$limit=null,$groupBy=null)
	{
		$this->sort = $sort;
		$this->limit = $limit;
		$this->groupBy = $groupBy;
		$this->joins = '';

		$options = array();
		if (isset($fields['id'])) { $options[] = "m.id='$fields[id]'"; }
		if (isset($fields['filename'])) { $options[] = "m.filename='$fields[filename]'"; }
		if (isset($fields['mime_type'])) { $options[] = "m.mime_type='$fields[mime_type]'"; }
		if (isset($fields['media_type'])) { $options[] = "m.media_type='$fields[media_type]'"; }
		if (isset($fields['title'])) { $options[] = "m.title='$fields[title]'"; }
		if (isset($fields['description'])) { $options[] = "m.description='$fields[description]'"; }
		if (isset($fields['md5'])) { $options[] = "m.md5='$fields[md5]'"; }
		if (isset($fields['user_id'])) { $options[] = "m.user_id='$fields[user_id]'"; }
		if (isset($fields['roll_id'])) { $options[] = "m.roll_id='$fields[roll_id]'"; }
		if (isset($fields['date'])) { $options[] = "m.date='$fields[date]'"; }
		if (isset($fields['city'])) { $options[] = "m.city='$fields[city]'"; }
		if (isset($fields['state'])) { $options[] = "m.state='$fields[state]'"; }
		if (isset($fields['country'])) { $options[] = "m.country='$fields[country]'"; }
		if (isset($fields['notes'])) { $options[] = "m.notes='$fields[notes]'"; }



		# Finding on fields from other tables required joining those tables.
		# You can add fields from other tables to $options by adding the join SQL
		# to $this->joins here
		if (isset($fields['tag_id']))
		{
			$this->joins.= ' left join media_tags mt on m.id=mt.media_id';
			$options[] = "mt.tag_id='$fields[tag_id]'";
		}
		if (isset($fields['tagList']))
		{
			$tags = $fields['tagList']->getSQL();
			$this->joins.= " inner join media_tags mt on m.id=mt.media_id and mt.tag_id in ($tags)";
			$this->groupBy = 'm.id having count(*)='.count($fields['tagList']);
		}
		if (isset($fields['tag_ids']))
		{
			$tags = implode(',',$fields['tag_ids']);
			$this->joins.= " inner join media_tags mt on m.id=mt.media_id and mt.tag_id in ($tags)";
			$this->groupBy = 'm.id having count(*)='.count($fields['tag_ids']);
		}

		$this->populateList($options);
	}

	protected function loadResult($key) { return new Media($this->list[$key]); }

	public function getTags()
	{
		if (count($this)) { return new TagList(array('mediaList'=>$this)); }
	}

	public function getCities()
	{
		$PDO = Database::getConnection();

		$query = $PDO->prepare("select distinct m.city from media m {$this->getJoins()} {$this->getWhere()} order by city");
		$query->execute();
		$result = $query->fetchAll();

		$cities = array();
		foreach($result as $row) { $cities[] = $row['city']; }
		return $cities;
	}
	public function getStates()
	{
		$PDO = Database::getConnection();

		$query = $PDO->prepare("select distinct m.state from media m {$this->getJoins()} {$this->getWhere()} order by state");
		$query->execute();
		$result = $query->fetchAll();

		$states = array();
		foreach($result as $row) { $states[] = $row['state']; }
		return $states;
	}
	public function getCountries()
	{
		$PDO = Database::getConnection();

		$query = $PDO->prepare("select distinct m.country from media m {$this->getJoins()} {$this->getWhere()} order by country");
		$query->execute();
		$result = $query->fetchAll();

		$countries = array();
		foreach($result as $row) { $countries[] = $row['country']; }
		return $countries;
	}
}
