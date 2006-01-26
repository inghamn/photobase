<?php
	session_start();
	mysql_connect("localhost","username","password");
	mysql_select_db("database") or die(mysql_error());

	$_POST['categories'] = implode(",",$_POST['categories']);
	$_POST['notes'] = htmlspecialchars($_POST['notes'],ENT_QUOTES);
	$_POST['keywords'] = htmlspecialchars($_POST['keywords'],ENT_QUOTES);
	$_POST['city'] = htmlspecialchars($_POST['city'],ENT_QUOTES);
	$_POST['state'] = htmlspecialchars($_POST['state'],ENT_QUOTES);

	$_POST['caption'] = str_replace("'","&#39;",$_POST['caption']);
	$_POST['caption'] = str_replace('"',"&quot;",$_POST['caption']);

	if (($_POST['year'])||($_POST['month'])||($_POST['day']))
	{
		if (is_numeric($_POST['year'])) { $date = str_pad($_POST['year'],4,"0",STR_PAD_RIGHT); }
		else { $date = "0000"; }

		if (is_numeric($_POST['month'])) { $date.=str_pad($_POST['month'],2,"0",STR_PAD_LEFT); }
		else { $date.="00"; }

		if (is_numeric($_POST['day'])) { $date.=str_pad($_POST['day'],2,"0",STR_PAD_LEFT); }
		else { $date.="00"; }
	}
	else { $date = "NULL"; }

	$sql = "update photos set
			categories='$_POST[categories]',
			keywords='$_POST[keywords]',
			notes='$_POST[notes]',
			city='$_POST[city]',
			state='$_POST[state]',
			caption='$_POST[caption]',
			date=$date
			where recordNum=$_POST[recordNum]";

	mysql_query($sql) or die($sql.mysql_error());

	Header("Location: ../home.php?viewPhoto=$_POST[offset]");
?>
