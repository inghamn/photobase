<?php
/**
 * @copyright Copyright (C) 2006,2007 City of Bloomington, Indiana. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 *
 * Defines the overall page layout
 */
class Template extends View
{
	private $filename;
	public $outputFormat = 'html';
	public $blocks = array();

	public function __construct($filename='default',$outputFormat='html',array $vars=null)
	{
		$this->filename = $filename;
		$this->outputFormat = preg_replace('/[^a-zA-Z]/','',$outputFormat);

		# Make sure the output format exists
		if (!is_file(APPLICATION_HOME."/templates/{$this->outputFormat}/{$this->filename}.inc"))
		{
			$this->filename = 'default';
			$this->outputFormat = 'html';
		}

		if (count($vars))
		{
			foreach($vars as $name=>$value) { $this->vars[$name] = $value; }
		}
	}

	# Template files must include a call to $this->includeBlocks(),
	# when they're ready for the main content
	public function render()
	{
		ob_start();
		include APPLICATION_HOME."/templates/{$this->outputFormat}/{$this->filename}.inc";
		return ob_get_clean();
	}

	# Callback function for template files
	private function includeBlocks()
	{
		ob_start();
		foreach($this->blocks as $block) { echo $block->render($this->outputFormat); }
		return ob_get_clean();
	}
}
