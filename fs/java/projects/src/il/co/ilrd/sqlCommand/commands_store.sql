USE computerStore;
/*1*/
SELECT modelID,
    processorSpeed,
    HDspace
FROM computer
WHERE (price < 600);
/*2*/
SELECT DISTINCT manuID
FROM printer;
/*3*/
SELECT modelID,
    RAM,
    screenSize
FROM computer
WHERE (
        price > 500
        and isLaptop = 1
    );
/*4*/
SELECT modelID
FROM printer
WHERE (isColor = 1);
/*5*/
SELECT modelID,
    processorSpeed,
    HDspace
FROM computer
WHERE (
        (
            CDdrive = 1000
            OR CDdrive = 500
        )
        and price < 600
    );
/*6*/
SELECT computer.processorSpeed,
    computerAndManu.manuID
FROM computer
    LEFT JOIN computerAndManu ON computer.modelID = computerAndManu.modelID
    and computer.ver = computerAndManu.ver
WHERE (
        computer.isLaptop = 1
        and computer.HDspace >= 1000
    );
/*7*/
SELECT computer.modelID,
    computer.price
FROM computer
    LEFT JOIN computerAndManu ON computer.modelID = computerAndManu.modelID
    and computer.ver = computerAndManu.ver
WHERE (computerAndManu.manuID = 30)
UNION
SELECT modelID,
    price
FROM printer
WHERE manuID = 30;
/*8*/
SELECT manuName
FROM manufacture
    JOIN computerAndManu ON manufacture.manuID = computerAndManu.manuID
    JOIN computer ON computer.modelID = computerAndManu.modelID
    and computer.ver = computerAndManu.ver
WHERE (computer.isLaptop = 0);
/*9*/
SELECT manuName
FROM manufacture
    JOIN computerAndManu ON manufacture.manuID = computerAndManu.manuID
    JOIN computer ON computer.modelID = computerAndManu.modelID
    and computer.ver = computerAndManu.ver
WHERE (
        computer.isLaptop = 1
        and processorSpeed > 500
    );
/*10*/
SELECT modelID,
    price
FROM printer
WHERE (
        price IN(
            SELECT MAX(price)
            FROM printer
        )
    );
/*11*/
SELECT AVG(processorSpeed)
FROM computer
WHERE (computer.isLaptop = 0);
/*12*/
SELECT AVG(processorSpeed)
FROM computer
WHERE (
        computer.isLaptop = 0
        and price > 1000
    );
/*13 find out the AVG speed of the PCs produced by manufactur A*/
SELECT AVG(processorSpeed)
FROM computer
    JOIN computerAndManu USING(modelID, ver)
    JOIN manufacture USING(manuID)
WHERE (
        manufacture.manuName = 'lg'
        AND computer.isLaptop = 0
    );
/*14 find out manufacturs who make 2 or more versions of a model of PC*/
SELECT manuName
FROM manufacture
    JOIN computerAndManu USING(manuID)
    JOIN computer USING(modelID, ver)
WHERE computer.isLaptop = 1
GROUP BY computerAndManu.modelID,
    computerAndManu.manuID
HAVING COUNT(computerAndManu.ver) > 1;
/*15 find the hard drive sizes that are equal among 2 or more PCs*/
SELECT CDdrive
FROM computer
WHERE computer.isLaptop = 0
GROUP BY computer.CDdrive
HAVING COUNT(computer.CDdrive) > 1;
/*16 find pair of PC model having identical speeds
 and RAM. As a result, each resulting pair is shown
 only once.
 result set- model with higher number, model with
 lower number, speed and RAM*/
SELECT DISTINCT t1.modelID AS model1,
    t2.modelID AS model2,
    t1.RAM,
    t1.processorSpeed
FROM computer t1
    JOIN computer t2 ON t1.RAM = t2.RAM
    AND t1.processorSpeed = t2.processorSpeed
    AND t1.modelID <> t2.modelID
WHERE t1.modelID > t2.modelID;
/*17 find the laptop models which they're speed is lower
 than the slowest PC*/
/*SELECT  modelID, isLeptop, processSpeed
 FROM Computer 
 WHERE processSpeed = (SELECT MIN(processSpeed) FROM Computer WHERE isLeptop = 1);*/
SELECT modelId,
    ver,
    processorSpeed
FROM computer
WHERE isLaptop = 1
    AND processorSpeed < (
        SELECT MIN(processorSpeed)
        FROM computer
        WHERE isLaptop = 0
    );
/*18 find manufactures of the cheapest color printer
 result set: manufacter, price*/
SELECT manufacture.manuName,
    printer.price
FROM manufacture
    JOIN printer USING(manuID)
WHERE printer.isColor = 1
    AND printer.price = (
        SELECT MIN(printer.price)
        FROM printe
    );
/*19 for each manufacter having models in laptop
 table, find out the average screen size of the laptop
 produced by it.
 result set: manufacturer, average screen size*/
SELECT manuName,
    AVG(screenSize)
FROM computer
    JOIN computerAndManu USING(modelID, ver)
    JOIN manufacture USING(manuID)
WHERE computer.isLaptop = 1
GROUP BY manuName;
/*20 find the manufacters producing at least 3
 distinct models of PCs*/
SELECT manuName
FROM manufacture
    JOIN computerAndManu USING(manuID)
GROUP BY manuName
HAVING COUNT(modelID) > 2;
/*21 list the highest priced PCs for each manufacturer*/
SELECT manuName,
    MAX(price)
FROM manufacture
    JOIN computerAndManu USING(manuID)
    JOIN computer USING(modelID, ver)
GROUP BY manuName;
/*22 for each value of PC speed that exceeds 600 MHz,
 define the average price of the PC's with identical
 speed*/
SELECT processorSpeed,
    AVG(price)
FROM computer
WHERE processorSpeed > 250
GROUP BY processorSpeed;
/*23 find the manufatures producing both pc having speed
 not less than 750 MHz and a laptop having speed not less
 than 750 MHz.
 result set- manufacturer*/
SELECT manuName
FROM manufacture
    JOIN computerAndManu USING (manuID)
    JOIN computer USING (modelID, ver)
WHERE processorSpeed >= 450
GROUP BY manufacture.manuName
HAVING COUNT(distinct computer.isLaptop) > 1;
/*24 find manufacturer who produce printers and also PCs 
 with the highest speed among the PCs with the lowest RAM*/
SELECT manuName,
    processorSpeed,
    RAM
FROM manufacture
    JOIN computerAndManu USING (manuID)
    JOIN computer USING (modelID, ver)
    JOIN printer USING(manuID)
WHERE RAM = (
        SELECT MIN(RAM)
        FROM computer
    ) processorSpeed = (
        SELECT MAX(processorSpeed)
        FROM computer
    )
    AND
GROUP BY manuName
HAVING COUNT(printer.manuID) > 0;
Select count(*) ct
from Recipe2 r2
    left join Recipe1 r1 on r2.Ingredient = r1.Ingredient
where r1.Ingredient is null
    /*25 define the average price of the PCs hard drive
     for each manufacturer that also produces printers.
     result set: menufacturer, average capacity of HD*/
SELECT AVG(computer.price)
FROM computer
    JOIN computerAndManu USING(modelID, ver)
    JOIN manufacture USING (manuID)
WHERE manufacture.manuName = 'lg';
/*26*/
SELECT manuName,
    AVG(CDdrive)
FROM computer
    JOIN computerAndManu USING(modelID, ver)
    JOIN manufacture USING (manuID)
    JOIN printer USING (manuID)
WHERE CDdrive > 0
GROUP BY manufacture.manuName;
/*27*/
INSERT INTO computer (
        modelId,
        ver,
        RAM,
        processorSpeed,
        HDspace,
        CDdrive,
        price
    )
SELECT modelId + 1000,
    MIN(ver) + 20,
    2 * MAX(RAM),
    MAX(processorSpeed),
    2 * MAX(HDspace),
    DEFAULT(CDdrive),
    MAX(price) / 1.5
FROM computer
WHERE isLaptop = 1
GROUP BY modelId;
/*28*/
DELETE FROM computer
WHERE HDspace = (
        SELECT *
        FROM (
                SELECT MIN(HDspace)
                FROM computer
            ) t1
    )
    OR RAM = (
        SELECT *
        FROM (
                SELECT MIN(RAM)
                FROM computer
            ) t2
    );