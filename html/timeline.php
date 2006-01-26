<table width="100%">
<tr><td width="100" valign="baseline">
		<a href="reset.php"><img src="interface/reset.gif" border="0" alt="reset"></a>
	</td>

	<td><form name="year" method="post" action="setYear.php">
		<select name="year" onChange="document.year.submit();">
			<option value="0">Year</option>
			<?php
				$sql = "select distinct year(date) as year from photos $Options order by year";
				$result = mysql_query($sql) or die($sql.mysql_error());
				while ($row = mysql_fetch_array($result))
				{
					if (($row["year"])&&($firstYearOnPage == $row["year"])) { echo "<option selected>$row[year]</option>"; }
					else { if ($row["year"]) echo "<option>$row[year]</option>"; }
				}
			?>
		</select>
		</form>
	</td>

	<td><form name="stateForm" method="post" action="setLocation.php">
		<select name="state" onChange="document.stateForm.submit();">
			<option value="0">Location</option>
			<?php
				$sql = "select distinct state from photos $Options order by state";
				$result = mysql_query($sql) or die($sql.mysql_error());
				while ($row = mysql_fetch_array($result))
				{
					if (isset($_SESSION['STATE']) && $_SESSION['STATE'] == $row['state']) { echo "<option selected=\"selected\">$row[state]</option>"; }
					else { echo "<option>$row[state]</option>"; }
				}
			?>
		</select>
		</form>
	</td>

	<td><form name="keywords" method="post" action="setKeywords.php">
		<input name="keywords" value="<?php if(isset($_SESSION['KEYWORDS'])) echo $_SESSION['KEYWORDS']; ?>">
		<input type="image" src="interface/search.gif" align="absmiddle">
		</form>
	</td>
</tr>
</table>
