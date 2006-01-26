<?php
	$sql = "select * from photos $Options order by date,recordNum limit $_GET[editPhoto],1";

	$thisPhoto = mysql_fetch_array(mysql_query($sql)) or die($sql.mysql_error());

	list($basefilename,$ext) = explode(".",$thisPhoto['filename']);
	$date = explode("-",$thisPhoto['date']);
	$categories = explode(",",$thisPhoto['categories']);
?>
<form name="editForm" method="post" action="savePhotoInfo.php">
<input name="recordNum" type="hidden" value="<?php echo $thisPhoto['recordNum']; ?>">
<input name="offset" type="hidden" value="<?php echo $_GET['editPhoto']; ?>">

<table>
<tr><td colspan="2">
		<label for="keywords" class="category1">Keywords:</label>
		<input name="keywords" size="40" value="<?php echo $thisPhoto['keywords']; ?>">
</td></tr>

<tr valign="top">
	<td><label for="categories" class="category1">Categories</label><br>
		<?php
		for($i=0; $i<8; $i++)
		{
			echo "<select name=\"categories[$i]\">";
			include ("options.php");
			echo "</select><br>";
		}
		?>
		<br>
		<label for="city" class="category1">City:</label>
		<input name="city" value="<?php echo $thisPhoto['city']; ?>"><br>

		<label for="state" class="category1">State:</label><br>
		<input name="state" value="<?php echo $thisPhoto['state']; ?>"><br>

		<span class="category1">Date:</span><br>
		<input name="month" size="2" maxlength="2" value="<?php echo $date[1]; ?>">
		<input name="day" size="2" maxlength="2" value="<?php echo $date[2]; ?>">
		<input name="year" size="4" maxlength="4" value="<?php echo $date[0]; ?>">
	</td>

	<td>
		<img src="../smallPhotos/<?php echo $basefilename; ?>.jpg" border="0" alt="<?php echo $thisPhoto['caption']; ?>">
	</td>
</tr>

<tr><td colspan="2">
		<label for="caption" class="category1">Caption:</label><br>
		<textarea name="caption" rows="4" cols="55"><?php echo $thisPhoto['caption']; ?></textarea>
	</td>
</tr>

<tr><td colspan="2">
		<label for="notes" class="category1">Notes:</label><br>
		<textarea name="notes" rows="4" cols="55"><?php echo $thisPhoto['notes']; ?></textarea>
	</td>
</tr>

<tr><td colspan="2" align="center">
		<input type="image" src="../interface/save.gif">
		<a href="../home.php"><img src="../interface/cancel.gif" border="0" alt="Cancel"></a>
	</td></tr>
</table>
</form>
