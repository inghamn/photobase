<?php
/**
 * @copyright Copyright (C) 2008 Cliff Ingham. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
?>
<h1>Uploads</h1>
<form method="post" action="<?php echo $_SERVER['SCRIPT_NAME']; ?>" enctype="multipart/form-data">
<fieldset><legend>Upload a single photo</legend>
	<p>Use this form to add a single photo to your pending uploads.</p>
	<input type="file" name="mediafile" />
	<button type="submit" class="upload">Upload</button>
</fieldset>
</form>

<form>
<fieldset><legend>Multi File Upload</legend>
	<p>You can use this applet to upload multiple files at once.</p>
	<div>
	<applet name="postlet" code="Main.class" archive="<?php echo BASE_URL; ?>/uploads/postlet.jar" width="305" height="150" mayscript="true">
		<param name = "maxthreads"		value = "1" />
		<param name = "language"		value = "" />
		<param name = "type"			value = "application/x-java-applet;version=1.3.1" />
		<param name = "destination"		value = "<?php echo BASE_URL; ?>/uploads/postletUpload.php" />
		<param name = "backgroundcolour" value = "16777215" />
		<param name = "tableheaderbackgroundcolour" value = "14079989" />
		<param name = "tableheadercolour" value = "0" />
		<param name = "warnmessage" value = "true" />
		<param name = "autoupload" value = "false" />
		<param name = "helpbutton" value = "false" />
		<param name = "fileextensions" value = "Image Files,jpg,gif,png,tiff" />
		<param name = "endpage" value = "<?php echo BASE_URL; ?>/uploads" />
		<param name = "helppage" value = "http://www.postlet.com/help" />
	</applet>
	</div>
</div>
</form>
