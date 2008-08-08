<?php
/**
 * @copyright Copyright (C) 2008 Cliff Ingham. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param User $this->user
 */
?>
<h1>Import Photos</h1>
<form method="post" action="<?php echo $_SERVER['SCRIPT_NAME']; ?>">
<fieldset><legend>Photos ready to import</legend>
<p>To import these photos as a roll, type in a name for the roll, and hit the import button.</p>
	<input name="roll_name" />
	<button type="submit">Import</button>

	<div>
	<?php
	if ($this->user->hasUploads())
	{
		foreach($this->user->getUploadDirectory() as $upload)
		{
			if ($upload->isFile())
			{
				$image = new Media();
				$image->setFile($upload->getPathname());

				echo "
				<span class=\"image thumbnail\">
					<img src=\"".BASE_URL."/uploads/thumbnail.php?image=$upload\" />
				</span>
				";
			}
		}
	}
	?>
	</div>
</fieldset>
</form>
