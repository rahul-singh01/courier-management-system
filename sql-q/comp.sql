CREATE TABLE companies (
    -- id BINARY(16) NOT NULL,
    sn int unsigned NOT NULL AUTO_INCREMENT,
    date DATETIME NOT NULL DEFAULT NOW(),
    
    name varchar(255) NOT NULL,
    address varchar(255) default NULL,
    city varchar(255) default NULL,
    state varchar(255) default NULL,
    zip int unsigned default NULL,
    phone bigint unsigned NOT NULL,
    fax varchar(255) default NULL,
    email varchar(255) UNIQUE default NULL,
    url varchar(255) default NULL,

    passwd_hash varchar(64) NOT NULL,

    total_orders int unsigned NOT NULL default '0',

    PRIMARY KEY (sn)
    -- INDEX (sn)
);