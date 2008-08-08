<?php
/**
 * @copyright Copyright (C) 2006-2008 Cliff Ingham. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @param MediaList $this->mediaList
 */
?>
<div class="left sidebar">
	<div class="tags"><h1>Tags</h1>
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
	<div><h1>Rolls</h1>
		<ul><?php
				$list = new RollList();
				$list->find();
				foreach($list as $roll)
				{
					$name = View::escape($roll->getName());
					echo "<li><a href=\"{$roll->getURL()}\">$name</a></li>";
				}
			?>
		</ul>
	</div>
	<div><h1>Location</h1>
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
<?php
	if (userHasRole('Administrator'))
	{
		include APPLICATION_HOME.'/includes/sidebarBoxes/Administrator.inc';
	}
?>
</div>
