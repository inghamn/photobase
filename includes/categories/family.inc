<ul><li><a href="home.php?category=Gainer">Gainer</a><?php if (isset($_SESSION['CATEGORY']) && in_array($_SESSION['CATEGORY'],$gainer)) include("$APPLICATION_HOME/includes/categories/gainer.php"); ?></li>
	<li><a href="home.php?category=Ingham">Ingham</a><?php if (isset($_SESSION['CATEGORY']) && in_array($_SESSION['CATEGORY'],$ingham)) include("$APPLICATION_HOME/includes/categories/ingham.php"); ?></li>
	<li><a href="home.php?category=Sultana">Sultana</a><?php if (isset($_SESSION['CATEGORY']) && in_array($_SESSION['CATEGORY'],$sultana)) include("$APPLICATION_HOME/includes/categories/sultana.php"); ?></li>
	<li><a href="home.php?category=Eskite">Eskite</a></li>
	<li><a href="home.php?category=Johnson">Johnson</a></li>
</ul>
