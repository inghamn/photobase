<?php
/**
 * @copyright Copyright (C) 2008 Cliff Ingham. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
class TagList extends PDOResultIterator
{
	public function __construct($fields=null)
	{
		$this->select = 'select distinct t.id as id from tags t';
		if (is_array($fields)) $this->find($fields);
	}

	public function find($fields=null,$sort='name',$limit=null,$groupBy=null)
	{
		$this->sort = $sort;
		$this->limit = $limit;
		$this->groupBy = $groupBy;
		$this->joins = '';

		$options = array();
		if (isset($fields['id'])) { $options[] = "t.id='$fields[id]'"; }
		if (isset($fields['name'])) { $options[] = "t.name='$fields[name]'"; }


		# Finding on fields from other tables required joining those tables.
		# You can add fields from other tables to $options by adding the join SQL
		# to $this->joins here
		if (isset($fields['media_id']))
		{
			$this->joins.= ' left join media_tags mt on t.id=mt.tag_id';
			$options[] = "mt.media_id='$fields[media_id]'";
		}

		if ($this->sort == 'popularity')
		{
			$this->select = 'select t.id as id,count(p.media_id) as popularity from tags t';
			$this->joins.= ' left join media_tags mt on t.id=mt.tag_id';
			$this->groupBy = 't.id';
		}

		if (isset($fields['mediaList']))
		{
			$media = $fields['mediaList']->getSQL();

			$this->joins.= ' join media_tags mt on t.id=mt.tag_id';
			$this->joins.= " join ($media)related_media on mt.media_id=related_media.id";
		}

		if (isset($fields['tag_ids']))
		{
			$tags = implode(',',$fields['tag_ids']);
			$this->joins.= " inner join media_tags mt on t.id=mt.tag_id and mt.media_id in
							(select media_id from media_tags where tag_id in ($tags))";
		}

		$this->populateList($options);
	}

	protected function loadResult($key) { return new Tag($this->list[$key]); }

	/**
	 * Returns all the tag names in the list, seperated by spaces
	 * @return string
	 */
	public function serialize()
	{
		$string = array();
		foreach($this as $tag) { $string[] = $tag->getName(); }
		return implode(' ',$string);
	}

	public function getMedia()
	{
		if (count($this))
		{
			return new MediaList(array('tagList'=>$this));
		}
	}
}
