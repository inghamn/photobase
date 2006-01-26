<?php
	session_start();
	mysql_connect("localhost","username","password");
	mysql_select_db("database") or die(mysql_error());

	# This grabs the process time for debugging purposes.
	#$startArray = explode(" ",microtime());

	#---------------------------------------------------------------------
	# Set up the options that all of the rest of the scripts are going to use.
	# They'll use these options, even if they will be using their own
	# SELECT and ORDER. This is to make sure that all the scripts will
	# be working with the same set of photos.
	#---------------------------------------------------------------------
	$Options = "";
	if (isset($_SESSION['CATEGORY']) && $_SESSION['CATEGORY']) { $Options = "where categories like '%$_SESSION[CATEGORY]%'"; }
	if (isset($_SESSION['STATE']) && $_SESSION['STATE'])
	{
		if ($Options) { $Options.=" and state='$_SESSION[STATE]'"; }
		else { $Options = "where state='$_SESSION[STATE]'"; }
	}
	if (isset($_SESSION['KEYWORDS']) && $_SESSION['KEYWORDS'])
	{
		if ($Options) { $Options.=" and match(city,keywords,caption,notes) against('$_SESSION[KEYWORDS]')"; }
		else { $Options = "where match(city,keywords,caption,notes) against('$_SESSION[KEYWORDS]')"; }
	}

	#---------------------------------------------------------------------
	# If the YEAR is set, we need to find the FIRSTREC with that year.
	#---------------------------------------------------------------------
	$sql = "select recordNum,year(date) as year from photos $Options order by date,recordNum";
	$completeYearList = mysql_query($sql) or die(mysql_error());

	if (isset($_SESSION['YEAR']) && $_SESSION['YEAR'])
	{
		$c=0;
		while ($row = mysql_fetch_array($completeYearList))
		{
			if ($row['year'] == $_SESSION['YEAR'])
			{
				$_SESSION['FIRSTREC'] = $c;
				break;
			}
			$c++;
		}
	}

	#---------------------------------------------------------------------
	# FIRSTREC should be set by now, if not - then we're starting fresh anyway
	# Grab the 15 photos we're going to display in the grid.
	#---------------------------------------------------------------------
	if (!isset($_SESSION['FIRSTREC'])) { $_SESSION['FIRSTREC'] = 0; }
	$sql = "select recordNum,filename,state,caption,year(date) as year from photos $Options order by date,recordNum limit $_SESSION[FIRSTREC],15";
	$gridPhotos = mysql_query($sql) or die($sql.mysql_error());

	# If the current firstRec doesn't point to any photos, reset to 0 and reselect
	if (!mysql_num_rows($gridPhotos))
	{
		$_SESSION['FIRSTREC'] = 0;
		$sql = "select recordNum,filename,state,caption,year(date) as year from photos $Options order by date,recordNum limit $_SESSION[FIRSTREC],15";
		$gridPhotos = mysql_query($sql) or die($sql.mysql_error());
	}

	#---------------------------------------------------------------------
	# If there still aren't any photos in $gridPhotos, then there just aren't
	# any that match what they selected.  This is most likely because they
	# have something typed in the Keywords field.  We need to just come out
	# and tell them that no photos match their selections
	#---------------------------------------------------------------------
	if (mysql_num_rows($gridPhotos))
	{
		# Grab the first year listed so we can display it in the YEAR drop-down
		$firstYearOnPage = mysql_result($gridPhotos,0,3);
		mysql_data_seek($gridPhotos,0);
	}
	else { $noPhotosMatch = 1; }
?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<link rel="stylesheet" href="album.css" type="text/css">
<title>Family Album</title>
</head>

<body marginwidth="0" marginheight="0">
<table width="640">
<tr><td colspan="2" height="60" valign="top">
		<?php include ("timeline.php"); ?>
</td></tr>

<tr><td width="120" valign="top">
		<?php include ("categories.php"); ?>
	</td>

	<td valign="top" width="520" align="center">
		<?php
			if (isset($_GET['viewPhoto'])) { include ("viewPhoto.php"); }
			elseif (isset($_GET['editPhoto'])) { include ("editPhoto.php"); }
			elseif (isset($_GET['noPhotosMatch'])) { include ("noPhotosMatch.php"); }
			else { include ("grid.php"); }

			echo "<p>".mysql_num_rows($completeYearList)." photos</p>";

			#--------------------------------------------------------------------
			# Debugging Stuff
			#--------------------------------------------------------------------
			#echo "<p>";
			#if (session_is_registered("YEAR")) { echo "Year=$YEAR "; }
			#if (session_is_registered("FIRSTREC")) { echo "FirstRec=$FIRSTREC"; }
			#if ($Options) { echo "Options=$Options"; }
			#echo "</p>";

		?>
	</td>
</tr>
</table>
<?php
	#------------------------------------------------------------
	# Before we quit, calculate how long it took to display this page.
	# For debugging purposes.
	#------------------------------------------------------------
	#$endArray = explode(" ",microtime());
	#$processTime = ((int)$endArray[1] + (float)$endArray[0]) - ((int)$startArray[1] + (float)$startArray[0]);
	#echo "<p align=\"center\">ProcessTime: $processTime seconds</p>";
?>
</body>
</html>