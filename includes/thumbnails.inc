<div id="main">
<?php
	while($row = mysql_fetch_array($photos))
	{
		list($basefilename,$extension) = explode(".",$row['filename']);
		echo "
		<div class=\"thumbnail\">
			<img src=\"http://aoi.pop.indiana.edu/~ningham/album/thumbs/$basefilename.gif\" alt=\"\" />
			<div>$row[state] $row[year]</div>
		</div>
		";
	}
?>
</div>

<div id="navigation">
<?php
	#---------------------------------------------------------------------
	# Display back button
	#---------------------------------------------------------------------
	if ($_SESSION['FIRSTREC'] != 0)
	{
		$previousRec = $_SESSION['FIRSTREC'] - 15;
		if ($previousRec < 0) { $previousRec = 0; }
		echo "<button class=\"back\" onclick=\"document.location.href='setFirstRec.php?firstRec=$previousRec'\">Back</button>";
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
		echo "<button class=\"next\" onclick=\"document.location.href='setFirstRec.php?firstRec=$lastRec'\">Next</button>";
	}
?>
</div>