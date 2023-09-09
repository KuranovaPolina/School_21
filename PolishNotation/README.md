Educational project Polish notation from organization «School 21».

* ***Task***

Develop an src/graph.c program in C for creating graphs of functions defined by arbitrary expressions. To calculate the values ​​of expressions, use Dijkstra's algorithm for translating expressions into Polish notation. The program is assembled using a Makefile. The name of the build stage is all. The executable file must be stored at the root in the build folder named graph.

* ***Conditions***

The size of the field for displaying graphs is a rectangle of 25 by 80 points.

Definition area - [0; 4 Pi]

Range of values - [-1; 1]

Orientation of the coordinate plane - the ordinate axis is directed downward, the abscissa axis is directed to the right.

The center of coordinates is middle of the left border (point {0, 13}).

You don't need to draw axes. 

Nothing but the graph should be displayed.

Values are rounded according to the rules of mathematics.

* ***Graphics***
  
The field should be displayed using Star symbol for the chart line and "." for the rest of the screen space.

* ***Modules***

Expression parsing and creating a list of lexical units.

Translation into Polish notation and calculation using this notation.

Drawing a graph in the terminal.

 library for organizing dynamic data structures (stack, list, etc.).

## Important notes:

* The game must be written in C, have a structured style, and run from the terminal; 
  
* Your source code will be tested by the static analyzer `cppcheck`, as well as the style linter `cpplint`. 
  
* Instructions on how to run these tests on your computer are in the `materials` folder. 
  
* We also recommend taking a look at the `code-samples` folder.

* Check your program for memory leaks!

* When developing the game, follow 
the principles of structured programming of E. Dijkstra.

> Possible operations & functions \
> "+" \
> "-" (unary and binary) \
> "*" \
> "/" \
> "()" \
> sin(x) \
> cos(x) \
> tan(x) \
> ctg(x) \
> sqrt(x) \
> ln(x)
