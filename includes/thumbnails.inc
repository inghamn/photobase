<div id="thumbnails">
	<?php
		$sql = "select * from photos";
		$photos = mysql_query($sql) or die($sql.mysql_error());
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
	<div id="navigation">
		<button type="button" class="back" onclick="document.location.href='';">Back</button>
		<button type="button" class="next" onclick="document.location.href='';">Next</button>
	</div>
</div>
