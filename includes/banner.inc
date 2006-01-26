<div id="banner">
	<a href="reset.php"><img src="images/reset.gif" alt="Reset" /></a>

	<form method="post" action="setYear.php">
	<select name="year" id="year" onchange="this.form.submit();">
		<option value="">Year</option>
		<?php
			$firstPhoto = mysql_fetch_array($photos);
			mysql_data_seek($photos,0);

			if (isset($firstPhoto['date']))
			{
				$firstDate = explode("-",$firstPhoto['date']);
			}

			$sql = "select distinct year(date) as year from photos $Options order by year";
			$result = mysql_query($sql) or die($sql.mysql_error());
			while(list($year) = mysql_fetch_array($result))
			{
				if ($year)
				{
					if (isset($firstDate) && $firstDate[2] == $year) { echo "<option selected=\"selected\">$year</option>"; }
					else { echo "<option>$year</option>"; }
				}
			}
		?>

	</select>
	</form>
	<form method="post" action="setState.php">
	<select name="state" id="state" onchange="this.form.submit();">
		<option value="">State</option>
		<?php
			$sql = "select distinct state from photos $Options order by state";
			$result = mysql_query($sql) or die($sql.mysql_error());
			while(list($state) = mysql_fetch_array($result))
			{
				if (isset($_SESSION['STATE']) && $state==$_SESSION['STATE']) echo "<option selected=\"selected\">$state</option>";
				else echo "<option>$state</option>";
			}
		?>

	</select>
	</form>
	<form method="post" action="setCountry.php">
	<select name="country" id="country" onchhange="this.form.submit();">
		<option value="">Country</option>
		<?php
			$sql = "select distinct country from photos $Options order by country";
			$result = mysql_query($sql) or die($sql.mysql_error());
			while(list($country) = mysql_fetch_array($result))
			{
				if (isset($_SESSION['COUNTRY']) && $country==$_SESSION['COUNTRY']) echo "<option selected=\"selected\">$country</option>";
				else echo "<option>$country</option>";
			}
		?>

	</select>
	<form method="get" action="home.php">
	<label>Keywords:<input name="keywords" id="keywords" <?php if (isset($_SESSION['KEYWORDS'])) echo "value=\"$_SESSION[KEYWORDS]\""; ?> /></label>
	<input type="image" src="images/search.gif" />
	</form>
</div>
