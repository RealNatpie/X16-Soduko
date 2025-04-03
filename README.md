# Soduko Puzzle Solver

I recently built a reproduction kit Altair 8800, after years of wanting one and constantly being reminded  I could never afford one.   It gave me a new appreciation for what it was probably like getting a machine like that into the hands of the people.
The thing that struck me the most was just how powerful a tool it would have been to have one of these machines with a basic interpreter.  And I set of to find problems that a new computer in 1975 could have helped with.

A soduko solver was my first stop.  I had a go in basic but it took hours to solve some puzzles so I did some optimization and jumped up to C.

This seemed like a something the Commander X16 would have been good at if it was available at the time, so I plugged the solver into a new front end a created this Soduko solver for the Commander X16.

Bruit force solving soduko is trial on modern computers.   I set out do do it once before and lost interest when I discovered there was no reason to do any optimizing as it solved any problem in milliseconds.    On slower 8bit processors its worth investing a little time into optimizing, and this solver employs four strategies to optimize the process.

 - Precompute and create lookup tables
 - Precache possible solutions for each blank
 - Fill in any blanks were only one possible answer exists
 - Solve starting with the squares with the fewest possibility to reduce branch exploration

The code was wirtten for the cc65 cross compiler.[Github Page](https://github.com/cc65/cc65)
There is a make file but if you need to compile manualy you can use:

    cl65 -o SODUKO.PRG -t cx16 soduko.c draw.c input.c solver.c
![sample puzzle](https://github.com/RealNatpie/X16-Soduko/blob/main/images/sample.jpg?raw=true)
Looking for a puzzle to solve.   Try this one.   Its one I've found that doesn't solve quite as quickly as other puzzles.
