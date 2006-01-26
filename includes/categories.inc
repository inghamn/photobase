<?php
	$fauna = array("Fauna","Pets","Barnyard","Wildlife");
	$holidays = array("Holidays","Christmas","Easter","Halloween","Thanksgiving");
	$ingham = array("Ingham","Mary","Paul","Nathan","John","Daniel");
	$sultana = array("Sultana","Manuel","Mary","David","Aaron","Peter","Adam");
	$gainer = array("Gainer","Golda","Shane","Robin","Mary");

	$family = array("Family","Eskite","Johnson");
	$family = array_merge($family,$ingham,$sultana,$gainer);
?>
<div id="categories">
	<ul>
		<li><a href="home.php?category=Family">Family</a><?php if(isset($_SESSION['CATEGORY']) && in_array($_SESSION['CATEGORY'],$family)) include("$APPLICATION_HOME/includes/categories/family.php"); ?></li>
		<li><a href="home.php?category=Friends">Friends</a></li>
		<li><a href="home.php?category=Flora">Flora</a></li>
		<li><a href="home.php?category=Fauna">Fauna</a><?php if (isset($_SESSION['CATEGORY']) && in_array($_SESSION['CATEGORY'],$fauna)) include("$APPLICATION_HOME/includes/categories/fauna.php"); ?></li>
		<li><a href="home.php?category=Holidays">Holidays</a><?php if (isset($_SESSION['CATEGORY']) && in_array($_SESSION['CATEGORY'],$holidays)) include("$APPLICATION_HOME/includes/categories/holidays.php"); ?></li>
	</ul>
</div>