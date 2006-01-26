<table width="500">
<?php
	$offset = $_SESSION['FIRSTREC'];
	$c = 0;
	while ($row = mysql_fetch_array($gridPhotos))
	{
		list($basefilename,$ext) = explode(".",$row['filename']);

		# Don't bother showing a 0 if there is no year for a photo
		if (!$row['year']) { $row['year'] = ""; }

		if (($c==0)||($c==5)||($c==10)) { echo "<tr valign=\"top\">"; }
		echo "
		<td align=\"center\" width=\"80\" height=\"80\">
		<a href=\"home.php?viewPhoto=$offset\"><br>
		$basefilename<br>
		<img src=\"thumbs/$basefilename.gif\" border=\"0\" alt=\"$row[caption]\"></a><br>
		<span class=\"photoCaption\">$row[state] $row[year]</span></td>
		";
		if (($c==4)||($c==9)||($c==15)) { echo "</tr>"; }
		$c++;
		$offset++;
	}
?>
</table>
<br>
<?php
	#---------------------------------------------------------------------
	# Display back button
	#---------------------------------------------------------------------
	if ($_SESSION['FIRSTREC'] != 0)
	{
		$previousRec = $_SESSION['FIRSTREC'] - 15;
		if ($previousRec < 0) { $previousRec = 0; }
		echo "
		<a href=\"setFirstRec.php?firstRec=$previousRec\">
		<img src=\"interface/back.gif\" border=\"0\" alt=\"Back\"></a>
		";
	}

	#---------------------------------------------------------------------
	# There are 15 photos in between the back and next button
	#---------------------------------------------------------------------
	$lastRec = $_SESSION['FIRSTREC']+15;

	#---------------------------------------------------------------------
	# Display the Next button
	#---------------------------------------------------------------------
	$numPhotos = mysql_num_rows(mysql_query("select recordNum from photos $Options"));
	if ($lastRec < $numPhotos)
	{
		echo "
		<a href=\"setFirstRec.php?firstRec=$lastRec\">
		<img src=\"interface/next.gif\" border=\"0\" alt=\"Next\"></a>
		";
	}
?>