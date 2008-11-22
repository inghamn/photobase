<?php
/**
 * @copyright Copyright (C) 2007 Cliff Ingham. All rights reserved.
 * @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
 */
class Tag extends ActiveRecord
{
	private $id;
	private $name;

	/**
	 * This will load all fields in the table as properties of this class.
	 * You may want to replace this with, or add your own extra, custom loading
	 */
	public function __construct($id=null)
	{
		if ($id)
		{
			$PDO = Database::getConnection();

			if (ctype_digit($id)) { $sql = 'select * from tags where id=?'; }
			else { $sql = 'select * from tags where name=?'; }
			$query = $PDO->prepare($sql);
			$query->execute(array($id));

			$result = $query->fetchAll(PDO::FETCH_ASSOC);
			if (!count($result)) { throw new Exception('tags/unknownTag'); }
			foreach($result[0] as $field=>$value) { if ($value) $this->$field = $value; }
		}
		else
		{
			# This is where the code goes to generate a new, empty instance.
			# Set any default values for properties that need it here
		}
	}

	/**
	 * This generates generic SQL that should work right away.
	 * You can replace this $fields code with your own custom SQL
	 * for each property of this class,
	 */
	public function save()
	{
		# Check for required fields here.  Throw an exception if anything is missing.
		if (!$this->name) { throw new Exception('missingRequiredFields'); }

		$fields = array();
		$fields['name'] = $this->name ? $this->name : null;

		# Split the fields up into a preparedFields array and a values array.
		# PDO->execute cannot take an associative array for values, so we have
		# to strip out the keys from $fields
		$preparedFields = array();
		foreach($fields as $key=>$value)
		{
			$preparedFields[] = "$key=?";
			$values[] = $value;
		}
		$preparedFields = implode(",",$preparedFields);


		if ($this->id) { $this->update($values,$preparedFields); }
		else { $this->insert($values,$preparedFields); }
	}

	private function update($values,$preparedFields)
	{
		$PDO = Database::getConnection();

		$sql = "update tags set $preparedFields where id={$this->id}";
		$query = $PDO->prepare($sql);
		$query->execute($values);
	}

	private function insert($values,$preparedFields)
	{
		$PDO = Database::getConnection();

		$sql = "insert tags set $preparedFields";
		$query = $PDO->prepare($sql);
		$query->execute($values);
		$this->id = $PDO->lastInsertID();
	}

	public function getPopularity(MediaList $mediaList=null)
	{
		if ($this->id)
		{
			$PDO = Database::getConnection();
			$sql = 'select count(*) as popularity from media_tags mt where mt.tag_id=? group by mt.tag_id';

			$query = $PDO->prepare($sql);
			$query->execute(array($this->id));
			$result = $query->fetchAll();
			if (count($result))
			{
				return $result[0]['popularity'];
			}
		}
	}

	/**
	* Parses a String of Tags
	*
	* Tags are space delimited. Either single or double quotes mark a phrase.
	* Odd quotes will cause everything on their right to reflect as one single
	* tag or phrase. All white-space within a phrase is converted to single
	* space characters. Quotes burried within tags are ignored! Duplicate tags
	* are ignored, even duplicate phrases that are equivalent.
	* @param string $sTagString
	* @return Array
	*/
	public static function tokenize($sTagString)
	{
		$sTagString = strtolower($sTagString);

		$arTags = array();		// Array of Output
		$cPhraseQuote = null;	// Record of the quote that opened the current phrase
		$sPhrase = null;		// Temp storage for the current phrase we are building

		// Define some constants
		static $sTokens = " \r\n\t";	// Space, Return, Newline, Tab
		static $sQuotes = "'\"";		// Single and Double Quotes

		// Start the State Machine
		do
		{
			// Get the next token, which may be the first
			$sToken = isset($sToken)? strtok($sTokens) : strtok($sTagString, $sTokens);

			// Are there more tokens?
			if ($sToken === false)
			{
				// Ensure that the last phrase is marked as ended
				$cPhraseQuote = null;
			}
			else
			{
				// Are we within a phrase or not?
				if ($cPhraseQuote !== null)
				{
					// Will the current token end the phrase?
					if (substr($sToken, -1, 1) === $cPhraseQuote)
					{
						// Trim the last character and add to the current phrase, with a single leading space if necessary
						if (strlen($sToken) > 1) $sPhrase .= ((strlen($sPhrase) > 0)? ' ' : null) . substr($sToken, 0, -1);
						$cPhraseQuote = null;
					}
					else
					{
						// If not, add the token to the phrase, with a single leading space if necessary
						$sPhrase .= ((strlen($sPhrase) > 0)? ' ' : null) . $sToken;
					}
				}
				else
				{
					// Will the current token start a phrase?
					if (strpos($sQuotes, $sToken[0]) !== false)
					{
						// Will the current token end the phrase?
						if ((strlen($sToken) > 1) && ($sToken[0] === substr($sToken, -1, 1)))
						{
							// The current token begins AND ends the phrase, trim the quotes
							$sPhrase = substr($sToken, 1, -1);
						}
						else
						{
							// Remove the leading quote
							$sPhrase = substr($sToken, 1);
							$cPhraseQuote = $sToken[0];
						}
					}
					else
						$sPhrase = $sToken;
				}
			}

			// If, at this point, we are not within a phrase, the prepared phrase is complete and can be added to the array
			if (($cPhraseQuote === null) && ($sPhrase != null))
			{
				$sPhrase = strtolower($sPhrase);
				if (!in_array($sPhrase, $arTags)) $arTags[] = $sPhrase;
				$sPhrase = null;
			}
		}
		while ($sToken !== false);	// Stop when we receive FALSE from strtok()
		return $arTags;
	}

	public function __toString() { return $this->name; }

	/**
	 * Generic Getters
	 */
	public function getId() { return $this->id; }
	public function getName() { return $this->name; }

	/**
	 * Generic Setters
	 */
	public function setName($string) { $this->name = strtolower(trim($string)); }
}
