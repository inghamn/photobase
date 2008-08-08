<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
include '../configuration.inc';

$PDO = Database::getConnection();


$sql = "select id,categories from temp left join media on temp.filename=media.filename where id is not null";
$query = $PDO->query($sql);
$result = $query->fetchAll();
foreach($result as $row)
{
	$media = new Media($row['id']);
	
	$categories = explode(',',$row['categories']);
	foreach($categories as $category)
	{
		if ($category)
		{
			$tags = str_replace('-',' ',$category);
			$media->setTags($tags);
		}
	}
	
	try { $media->save(); }
	catch (Exception $e)
	{
		print_r($media);
		die(print_r($e));
	}
	echo $row['categories']."\n";
}