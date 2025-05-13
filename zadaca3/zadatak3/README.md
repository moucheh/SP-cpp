# Trip Planner

Implement a program for planning trips through Bosnia and Herzegovina. 
It is necessary to implement a class `TripPlanner` in which you will use a double linked list from the first task to store data about significant places on the route. 
The program should be able to add locations (with geographic coordinates), 
add stops along the route, remove stops, print the entire route, 
draw the route on a map, and print the total distance of the trip. 
When the program starts, it should look similar to this:

```plaintext
Choose option number:
  1. Add Location
  2. Add Stop
  3. Insert Stop
  4. Remove Stop
  5. Print Trip
  6. Show Trip Distance
  7. Render Trip
  8. Print Locations
  9. Exit
```

## Explanation of Each Option:

1. **Add Location**: Adds a new location to the list of possible places to visit (input format is arbitrary).
   A file `locations.txt` with several places within the country is provided, which should be loaded when the program starts.
3. **Add Stop**: Adds a stop along the route, the place is chosen by name based on the loaded/known locations.
4. **Insert Stop**: Unlike the previous command, adds a stop somewhere other than the end of the current route.
5. **Remove Stop**: Removes a stop from the route.
6. **Print Trip**: Prints all stops on the route.
7. **Show Trip Distance**: Prints the total distance of the trip from the first to the last place,
   use the method explained [here](https://www.geeksforgeeks.org/program-distance-two-points-earth/) for calculating distances.
9. **Render Trip**: Pritns the route to an HTML file with the format explained below,
    opening this file in a browser will show the route from the first to the last stop on the map of Bosnia and Herzegovina.
11. **Print Locations**: Prints all available locations.

## Drawing the Route on the Map

To correctly draw the route on the map, the provided template HTML file should be used. 
The output HTML file should be in the form:

```html
<template-file-content>
<your-content>
</svg>

```
In the your-content part, you need to add lines in the form:

```html
<line x1="" y1="" x2="" y2="" stroke="orange" stroke-width="4"></line>
```
Where x1, y1, x2, y2 represent the coordinates of two consecutive stops on the route
To calculate these values, use the following equations:

```cpp
x = (longitude - WESTEDGE) / (EASTEDGE - WESTEDGE) * IMAGEWIDTH;
y = (latitude - NORTHEDGE) / (SOUTHEDGE - NORTHEDGE) * IMAGEHEIGHT;
```

The constants are provided below:

```cpp
IMAGEWIDTH = 1063;
IMAGEHEIGHT = 1014;
NORTHEDGE = 45.4;
SOUTHEDGE = 42.4;
WESTEDGE = 15.5;
EASTEDGE = 19.9;
```
