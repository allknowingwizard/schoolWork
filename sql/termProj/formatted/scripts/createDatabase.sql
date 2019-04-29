use census;

create table if not exists state(
   state_name VARCHAR(40) NOT NULL,
   PRIMARY KEY ( state_name )
);

create table if not exists region(
	region_name VARCHAR(40) NOT NULL,
    PRIMARY KEY (region_name)
);

create table if not exists city(
	city_name VARCHAR(40) NOT NULL,
    PRIMARY KEY (city_name)
);

create table if not exists year(
	year INT NOT NULL,
    PRIMARY KEY(year)
);

create table if not exists state_measure(
	state_name VARCHAR(40) NOT NULL,
    population INT,
    year INT,
    number_of_reps INT,
    PRIMARY KEY (state_name, year),
    FOREIGN KEY (state_name) REFERENCES state(state_name),
    FOREIGN KEY (year) REFERENCES year(year)
);
create table if not exists city_measure(
	state_name VARCHAR(40) NOT NULL,
    city_name VARCHAR(40) NOT NULL,
    population INT NOT NULL,
    year INT NOT NULL,
    PRIMARY KEY (state_name, city_name, year),
    FOREIGN KEY (state_name) REFERENCES state(state_name),
    FOREIGN KEY (city_name) REFERENCES city(city_name),
    FOREIGN KEY (year) REFERENCES year(year)
);
create table if not exists region_measure(
	region_name VARCHAR(40) NOT NULL,
    population INT NOT NULL,
    year INT NOT NULL,
    number_of_reps INT NOT NULL,
    PRIMARY KEY (region_name, year),
    FOREIGN KEY (region_name) REFERENCES region(region_name),
    FOREIGN KEY (year) REFERENCES year(year)
);