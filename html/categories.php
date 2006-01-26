<?php
	$fauna = array("Fauna","Pets","Barnyard","Wildlife");
	$holidays = array("Holidays","Christmas","Easter","Halloween","Thanksgiving");
	$ingham = array("Ingham","Mary","Paul","Nathan","John","Daniel");
	$sultana = array("Sultana","Manuel","Mary","David","Aaron","Peter","Adam");
	$gainer = array("Gainer","Golda","Shane","Robin","Mary");

	$family = array("Family","Eskite","Johnson");
	$family = array_merge($family,$ingham,$sultana,$gainer);
?>
<table border="0" width="90" cellpadding="0" cellspacing="0">
<tr><td><a href="setCategory.php?category=Family">
		<img src="interface/family.gif" border="0" alt="Family"></a></td></tr>
		<?php if (isset($_SESSION['CATEGORY']) && in_array($_SESSION['CATEGORY'],$family)) { include ("categories/family.php"); } ?>
<tr><td><a href="setCategory.php?category=Friends">
		<img src="interface/friends.gif" border="0" alt="Friends"></a></td></tr>
<tr><td><a href="setCategory.php?category=Flora">
		<img src="interface/flora.gif" border="0" alt="Flora"></a></td></tr>
<tr><td><a href="setCategory.php?category=Fauna">
		<img src="interface/fauna.gif" border="0" alt="Fauna"></a></td></tr>
		<?php if(isset($_SESSION['CATEGORY']) && in_array($_SESSION['CATEGORY'],$fauna)) { include ("categories/fauna.php"); } ?>
<tr><td><a href="setCategory.php?category=Holidays">
		<img src="interface/holidays.gif" border="0" alt="Holidays"></a></td></tr>
		<?php if(isset($_SESSION['CATEGORY']) && in_array($_SESSION['CATEGORY'],$holidays)) { include ("categories/holidays.php"); } ?>
</table>