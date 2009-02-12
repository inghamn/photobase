<?php
/**
 * @copyright Copyright (C) 2008 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
include '../configuration.inc';
$PDO = Database::getConnection();

$rolls = new RollList();
$rolls->find();

$query = $PDO->prepare('select * from media where roll_id=? order by id');
foreach($rolls as $roll)
{
	$DATA = fopen(APPLICATION_HOME."/html/rolls/{$roll->getId()}/data.xml",'w');
	fwrite($DATA,"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");


	$name = View::escape($roll->getName());
	$xml = "
<roll name=\"$name\">
	<photos>
";

	$query->execute(array($roll->getId()));
	$result = $query->fetchAll(PDO::FETCH_ASSOC);
	foreach($result as $row)
	{
		$xml.= "\t\t<photo>\n";
		foreach($row as $field=>$value)
		{
			$tag = View::escape($field);
			$value = View::escape($value);
			$xml.= "\t\t\t<$tag>$value</$tag>\n";
		}
		$xml.= "\t\t</photo>\n\n";
	}

	$xml.= "
	</photos>
</roll>
";
	fwrite($DATA,$xml);
	fclose($DATA);
}
