<?php
	#---------------------------------------------------------------------
	# Send anything that comes in through GET to the session.
	#---------------------------------------------------------------------
	if (isset($_GET['category'])) { $_SESSION['CATEGORY'] = $_GET['category']; }
	if (isset($_GET['keywords']))
	{
		$_GET['keywords'] = sanitizeString($_GET['keywords']);
		$_SESSION['KEYWORDS'] = $_GET['keywords'];
	}

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
	$photos = mysql_query($sql) or die($sql.mysql_error());

	# If the current firstRec doesn't point to any photos, reset to 0 and reselect
	if (!mysql_num_rows($photos))
	{
		$_SESSION['FIRSTREC'] = 0;
		$sql = "select recordNum,filename,state,caption,year(date) as year from photos $Options order by date,recordNum limit $_SESSION[FIRSTREC],15";
		$photos = mysql_query($sql) or die($sql.mysql_error());
	}

	#---------------------------------------------------------------------
	# If there still aren't any photos in $photos, then there just aren't
	# any that match what they selected.  This is most likely because they
	# have something typed in the Keywords field.  We need to just come out
	# and tell them that no photos match their selections
	#---------------------------------------------------------------------
	if (mysql_num_rows($photos))
	{
		# Grab the first year listed so we can display it in the YEAR drop-down
		$firstYearOnPage = mysql_result($photos,0,3);
		mysql_data_seek($photos,0);
	}
	else { $noPhotosMatch = 1; }


	#-----------------------------------------------------------------------------------------
	# Now we actually start writing the HTML stuff.
	#-----------------------------------------------------------------------------------------
	include("$APPLICATION_HOME/includes/xhtmlHeader.inc");
	include("$APPLICATION_HOME/includes/banner.inc");
	include("$APPLICATION_HOME/includes/categories.inc");


	# If they don't want to see a particular photo, show them the thumbnails
	if (isset($_GET['viewPhoto'])) { include("$APPLICATION_HOME/includes/viewPhoto.inc"); }
	else { include("$APPLICATION_HOME/includes/thumbnails.inc"); }

	include("$APPLICATION_HOME/includes/xhtmlFooter.inc");
?>