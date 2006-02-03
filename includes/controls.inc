<div id="controls">
	<button type="button" class="reset" onclick="document.location.href='<?php echo $BASE_URL; ?>/reset.php';">Reset</button>

	<form method="post" action="setYear.php">
		<fieldset><legend>Year</legend>
			<select name="year" id="year" onchange="this.form.submit();">
				<option value="">Year</option>
				<?php
					$sql = "select distinct year(date) as year from photos order by year";
					$years = mysql_query($sql) or die($sql.mysql_error());
					while(list($year) = mysql_fetch_array($years))
					{
						echo "<option>$year</option>";
					}
				?>

			</select>
		</fieldset>
	</form>

	<form method="post" action="setState.php">
		<fieldset><legend>State</legend>
			<select name="state" id="state" onchange="this.form.submit();">
				<option value="">State</option>
				<?php
					$sql = "select distinct state from photos order by state";
					$states = mysql_query($sql) or die($sql.mysql_error());
					while(list($state) = mysql_fetch_array($states))
					{
						echo "<option>$state</option>";
					}
				?>

			</select>
		</fieldset>
	</form>

	<form method="post" action="setCountry.php">
		<fieldset><legend>Country</legend>
			<select name="country" id="country" onchhange="this.form.submit();">
				<option value="">Country</option>
				<?php
					$sql = "select distinct country from photos order by country";
					$result = mysql_query($sql) or die($sql.mysql_error());
					while(list($country) = mysql_fetch_array($result))
					{
						if (isset($_SESSION['COUNTRY']) && $country==$_SESSION['COUNTRY']) echo "<option selected=\"selected\">$country</option>";
						else echo "<option>$country</option>";
					}
				?>

			</select>
		</fieldset>
	</form>

	<form method="get" action="home.php">
		<fieldset><legend>Keywords</legend>
			<label>Keywords:<input name="keywords" id="keywords" <?php if (isset($_SESSION['KEYWORDS'])) echo "value=\"$_SESSION[KEYWORDS]\""; ?> /></label>
			<button type="submit" class="search">Search</button>
		</fieldset>
	</form>
</div>
