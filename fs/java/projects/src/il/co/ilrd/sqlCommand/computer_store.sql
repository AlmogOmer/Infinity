CREATE DATABASE IF NOT EXISTS computerStore;
USE computerStore;
CREATE TABLE IF NOT EXISTS computer(
    modelID int,
    RAM int,
    processorSpeed int,
    HDspace int,
    isLaptop boolean,
    CDdrive int,
    screenSize int,
    ver int,
    price int,
    PRIMARY KEY (modelID, ver)
);
CREATE TABLE IF NOT EXISTS manufacture(
    manuID int,
    manuName varchar(50),
    PRIMARY KEY (manuID)
);
CREATE TABLE IF NOT EXISTS printer(
    modelID int,
    manuID int,
    isColor boolean,
    price int,
    PRIMARY KEY (modelID),
    FOREIGN KEY(manuID) REFERENCES manufacture(manuID)
);
CREATE TABLE IF NOT EXISTS computerAndManu(
    modelID int,
    ver int,
    manuID int,
    FOREIGN KEY(modelID, ver) REFERENCES computer(modelID, ver),
    FOREIGN KEY(manuID) REFERENCES manufacture(manuID)
);