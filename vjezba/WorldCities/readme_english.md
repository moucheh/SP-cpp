# WorldCities Parser

Write a C++ program that parses the contents of the provided csv file _WorldCities.csv_.

-   The first line contains titles (this should be skipped)

Every line has the following data:

-   City name
-   Latitude
-   Longitude
-   Country
-   City status:
    -   _primary_ denotes a capital city
    -   _admin_ denotes a large city that is not a capital
    -   _minor_ denotes a small city
-   Population
-   Unique ID

It is necessary to implement a program that correctly loads the data from the file provided.
After that, the program should provide options to search for a city based on different criteria:

-   Print all cities from a certain country sorted by:
-   Population, when the user enters the corresponding command 
-   Name, when the user enters the corresponding command

Print all countries:

-   Sorted by population
-   Sorted by name

Country output should include:

-   Country name
-   Capital city
-   Largest city by population
-   Total population across all cities
-   Number of cities


  Print a city with all the data provided in the file

-   Print all capital cities with their respective countries
-   Print the largest cities, their population and which country they belong to

You should use the correct STL containers that provide optimal searching, sorting and data organization.
The program should run in a loop, allowing the user to enter commands as they wish.
You have the freedom to choose command names as you wish.
The list of commands should be printed when the program starts or when the user enters help
