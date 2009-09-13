<?php
/**
 * @copyright Copyright 2006-2009 Cliff Ingham
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param MediaList $this->mediaList
 */
?>
<div class="left sidebar">
<?php
	if (userHasRole('Administrator'))
	{
		include APPLICATION_HOME.'/includes/sidebarBoxes/Administrator.inc';
	}
?>
	<div class="tags"><h3>Tags</h3>
	<?php
		$tagList = new TagList();
		$fields = isset($this->mediaList) ? array('mediaList'=>$this->mediaList) : null;
		$tagList->find($fields);

		$maxPopularity = 0;
		$tags = array();
		foreach($tagList as $tag)
		{
			$popularity = isset($this->mediaList) ? $tag->getPopularity($this->mediaList) : $tag->getPopularity();
			if ($popularity > $maxPopularity) { $maxPopularity = $popularity; }

			$tags[$tag->getId()]['name'] = View::escape($tag->getName());
			$tags[$tag->getId()]['popularity'] = $popularity;
		}

		foreach($tags as $id=>$tag)
		{
			$percent = $tag['popularity'] / $maxPopularity * 100;

			if ($percent > 90) { $class = 'class="p90"'; }
			elseif ($percent > 70) { $class = 'class="p70"'; }
			elseif ($percent > 50) { $class = 'class="p50"'; }
			elseif ($percent > 30) { $class = 'class="p30"'; }
			elseif ($percent > 10) { $class = 'class="p10"'; }
			else { $class = 'class="p0"'; }

			echo "
			<span $class>
				<a href=\"".BASE_URL."/media?tag_id=$id\">$tag[name]</a>
			</span>
			";
		}

	?>
	</div>
	<div><h3>Location</h3>
		<form method="get" action="<?php echo BASE_URL; ?>/media">
		<fieldset>
			<table>
			<tr><td><label for="city">City</label></td>
				<td><select name="city" id="city" onchange="this.form.submit();">
						<option></option>
					<?php
						$media = isset($this->mediaList) ? $this->mediaList : new MediaList();
						foreach($media->getCities() as $city)
						{
							$selected = (isset($_SESSION['filters']['city']) && $_SESSION['filters']['city']==$city) ? ' selected="selected"' : '';
							$city = View::escape($city);
							echo "<option$selected>$city</option>";
						}
					?>
					</select>
				</td>
			</tr>
			<tr><td><label for="state">State</a></label></td>
				<td><select name="state" id="state" onchange="this.form.submit();">
						<option></option>
					<?php
						foreach($media->getStates() as $state)
						{
							$selected = (isset($_SESSION['filters']['state']) && $_SESSION['filters']['state']==$state) ? ' selected="selected"' : '';
							$state = View::escape($state);
							echo "<option$selected>$state</option>";
						}
					?>
					</select>
				</td>
			</tr>
			<tr><td><label for="country">Country</label></td>
				<td><select name="country" id="country" onchange="this.form.submit();">
						<option></option>
					<?php
						foreach($media->getCountries() as $country)
						{
							$selected = (isset($_SESSION['filters']['country']) && $_SESSION['filters']['country']==$country) ? ' selected="selected"' : '';
							$country = View::escape($country);
							echo "<option$selected>$country</option>";
						}
					?>
					</select>
				</td>
			</tr>
			</table>

			<button type="submit" class="submit">Submit</button>
		</fieldset>
		</form>
	</div>
	<div><h3>
			Albums
			<a class="add button" href="<?php echo BASE_URL; ?>/albums/addAlbum.php">Add</a>
		</h3>
	<?php
		$list = new AlbumList();
		$list->find();
		if (count($list))
		{
			echo "<ul>";
			foreach ($list as $album)
			{
				$name = View::escape($album->getName());
				echo "<li><a href=\"{$album->getURL()}\">$name</a></li>";
			}
			echo "</ul>";
		}
	?>
	</div>
	<div><h3>Rolls</h3>
		<form method="get" action="<?php echo BASE_URL; ?>/media">
			<fieldset>
				<select name="roll_id" onchange="this.form.submit();">
					<option></option>
					<?php
						$list = new RollList();
						$list->find();
						foreach($list as $roll)
						{
							$name = View::escape($roll->getName());
							echo "<option value=\"{$roll->getId()}\">$name</option>";
						}
					?>
				</select>
			</fieldset>
		</form>
	</div>
</div>
