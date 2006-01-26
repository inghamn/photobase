<?php
	$sql = "select recordNum,filename,caption,city,state,year(date) as year,monthname(date) as month,dayofmonth(date) as day
			from photos
			$Options order by date,recordNum limit $_GET[viewPhoto],1";
	$thisPhoto = mysql_fetch_array(mysql_query($sql)) or die($sql.mysql_error());

	list($basefilename,$ext) = explode(".",$thisPhoto['filename']);

	# If it's an image, use the javascript popUp
	if (($ext=="jpg")||($ext=="gif")) { echo "<a href=\"JavaScript:display();\">"; }
	# Otherwise, we don't know what kind of file it is.  Just write a link directly to it.
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
	echo "</div>";


	echo "<div id=\"navigation\">";
	#---------------------------------------------------------------------
	# Display back button
	#---------------------------------------------------------------------
	if ($_GET['viewPhoto'] != 0)
	{
		$previousPhoto = $_GET['viewPhoto'] - 1;
		echo "
		<a href=\"home.php?viewPhoto=$previousPhoto\">
		<img src=\"interface/back.gif\" border=\"0\" alt=\"Back\"></a>
		";
	}
	echo "
	<a href=\"home.php\"><img src=\"interface/grid.gif\" border=\"0\" alt=\"To Contact Sheet\"></a>
	";

	#---------------------------------------------------------------------
	# Display the Next button
	#---------------------------------------------------------------------
	$numPhotos = mysql_num_rows(mysql_query("select recordNum from photos $Options"));
	$nextPhoto = $_GET['viewPhoto'] + 1;
	if ($nextPhoto < $numPhotos)
	{
		echo "
		<a href=\"home.php?viewPhoto=$nextPhoto\">
		<img src=\"interface/next.gif\" border=\"0\" alt=\"Next\"></a>
		";
	}

	echo "
	</div>
	<p><a href=\"Edit/index.php?editPhoto=$_GET[viewPhoto]\">
	<img src=\"interface/edit.gif\" border=\"0\" alt=\"Edit Photo\"></a></p>
<script language=\"JavaScript\">
var win1 = window;

function display()
{
	var width,height;

	width = screen.width-20;
	height = screen.height-60;

	win1 = open('popUp.php?photo=$thisPhoto[recordNum]','POPUP', 'width='+width+',height='+height+',resizable=yes,scrollbars=yes');
	win1.moveTo(0,0);
	win1.focus();
}
</script>
	";
?>
