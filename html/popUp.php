<?php
	$sql = "select filename,caption from photos where recordNum=$_GET[photo]";
	$row = mysql_fetch_array(mysql_query($sql)) or die($sql.mysql_error());
?>
<html>
<body bgcolor="000000" text="ffffff">
<center>
<img src="bigPhotos/<?php echo $row['filename']; ?>" border="0" alt="<?php echo $row['caption']; ?>">
</center>

</body>
</html>