-- @copyright Copyright (C) 2006,2007 Cliff Ingham. All rights reserved.
-- @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
create table users (
	id int unsigned not null primary key auto_increment,
	username varchar(30) not null,
	password varchar(32) default null,
	authenticationMethod varchar(40) not null default 'local',
	firstname varchar(128) not null,
	lastname varchar(128) not null,
	email varchar(255) not null,
	unique key (username)
) engine=InnoDB;

CREATE TABLE roles (
	id int unsigned not null primary key auto_increment,
	role varchar(30) not null unique
) engine=InnoDB;
insert roles set role='Administrator';

CREATE TABLE user_roles (
	user_id int unsigned not null,
	role_id int unsigned not null,
	primary key (user_id,role_id),
	foreign key(user_id) references users (id),
	foreign key(role_id) references roles (id)
) engine=InnoDB;

create table rolls (
	id int unsigned not null primary key auto_increment,
	name varchar(128) not null,
	date date not null,
	user_id int unsigned not null,
	foreign key (user_id) references users(id)
) engine=InnoDB;

create table media (
	id int unsigned not null primary key auto_increment,
	filename varchar(128) not null,
	mime_type varchar(128) not null,
	media_type varchar(24) not null,
	title varchar(128),
	description text,
	md5 varchar(32) not null,
	user_id int unsigned not null,
	roll_id int unsigned not null,
	date datetime,
	year int(4) unsigned,
	city varchar(128),
	state varchar(128),
	country varchar(128),
	notes varchar(255),
	foreign key (user_id) references users(id),
	foreign key (roll_id) references rolls(id)
) engine=InnoDB;

create table tags (
	id int unsigned not null primary key auto_increment,
	name varchar(128) not null unique
) engine=InnoDB;

create table media_tags (
	media_id int unsigned not null,
	tag_id int unsigned not null,
	foreign key (media_id) references media(id),
	foreign key (tag_id) references tags(id)
) engine=InnoDB;
