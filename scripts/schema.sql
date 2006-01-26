--
-- Table structure for table photos
--
CREATE TABLE photos (
  recordNum smallint(5) unsigned NOT NULL auto_increment,
  filename varchar(50) NOT NULL default '',
  date date default NULL,
  city varchar(128) NOT NULL default '',
  state varchar(128) NOT NULL default '',
  country varchar(128) NOT NULL default '',
  categories varchar(255) NOT NULL default '',
  keywords varchar(255) NOT NULL default '',
  caption text NOT NULL,
  notes varchar(255) NOT NULL default '',
  PRIMARY KEY  (recordNum),
  KEY date (date),
  KEY state (state),
  FULLTEXT KEY SearchIndex (city,keywords,caption,notes)
);
