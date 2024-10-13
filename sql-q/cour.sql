CREATE TABLE couriers (
    -- id BINARY(16) NOT NULL,
    sn int unsigned NOT NULL AUTO_INCREMENT,
    date DATETIME NOT NULL DEFAULT NOW(),

    from_person int unsigned NOT NULL,
    to_person int unsigned NOT NULL,
    
    -- from_state varchar(255) default NULL, -- will fetch automatically from from_person address
    -- to_state varchar(255) default NULL,

    status varchar(15) NOT NULL,
    detail_status varchar(255) NOT NULL,
    content varchar(255) NOT NULL,
    
    company int unsigned NOT NULL,

    FOREIGN KEY (company) REFERENCES companies(sn),
    FOREIGN KEY (from_person) REFERENCES users(sn),
    FOREIGN KEY (to_person) REFERENCES users(sn),

    PRIMARY KEY (sn)
    -- INDEX (sn)
);
