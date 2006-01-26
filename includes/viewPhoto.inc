<div id="main">
<?php
	$sql = "select recordNum,filename,caption,city,state,year(date) as year,monthname(date) as month,dayofmonth(date) as day
			from photos $Options order by date,recordNum limit $_GET[viewPhoto],1";
	$thisPhoto = mysql_fetch_array(mysql_query($sql)) or die($sql.mysql_error());

	list($basefilename,$ext) = explode(".",$thisPhoto['filename']);

	# If it's an image, use the javascript popUp
	# Otherwise, we don't know what kind of file it is.  Just write a link directly to it.
	if (($ext=="jpg")||($ext=="gif")) { echo "<a href=\"JavaScript:display();\">"; }
	else { echo "<a href=\"bigPhotos/$thisPhoto[filename]\">"; }

	echo "
	<img src=\"smallPhotos/$basefilename.jpg\" border=\"0\" alt=\"$thisPhoto[caption]\"></a><br>
	<div id=\"caption\">$thisPhoto[caption]</div>
	<div id=\"location\">$thisPhoto[city] $thisPhoto[state]</div>
	<div id=\"date\">
	";
		if ($thisPhoto['month']) { echo "$thisPhoto[month] "; }
		if ($thisPhoto['day']) { echo "$thisPhoto[day],"; }
		if ($thisPhoto['year']) { echo "$thisPhoto[year]<BR>"; }
?>
</div>

<div id="navigation">
<?php
	#---------------------------------------------------------------------
	# Display back button
	#---------------------------------------------------------------------
	if ($_GET['viewPhoto'] != 0)
	{
		$previousPhoto = $_GET['viewPhoto'] - 1;
		echo "<button class=\"back\" onclick=\"document.location.href='home.php?viewPhoto=$previousPhoto'\">Back</button>";
	}
	echo "<button class=\"home\" onclick=\"document.location.href='home.php'\">To Contact Sheet</button>";

	#---------------------------------------------------------------------
	# Display the Next button
	#---------------------------------------------------------------------
	$numPhotos = mysql_num_rows(mysql_query("select recordNum from photos $Options"));
	$nextPhoto = $_GET['viewPhoto'] + 1;
	if ($nextPhoto < $numPhotos)
	{
		echo "<button class=\"next\" onclick=\"document.location.href='home.php?viewPhoto=$nextPhoto'\">Next</button>";
	}

	echo "<p><a href=\"Edit/index.php?editPhoto=$_GET[viewPhoto]\"><img src=\"interface/edit.gif\" border=\"0\" alt=\"Edit Photo\"></a></p>";
?>
</div>