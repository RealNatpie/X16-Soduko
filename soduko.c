#include "soduko.h"



int puzzle[81];
int blanks[82];
int colAdds[9][9];
int rowAdds[9][9];
int celAdds[9][9];
int AddCol[81];
int AddRow[81];
int AddCel[81];
int posBlanks[81][10];
int slvOrder[81];
int puzxLoc, puzyLoc;
clock_t cursorTickTime;
void main()
{
    cursorTickTime = CLOCKS_PER_SEC / 4;  //Sets timing for cursor blinking.  
    clrscr();
    splash();
    initLookup();
    printf("Preare to enter puzzle.\n");
    inputPuz();
    printf("Checking complexity.\n");
    findBlanks();
    printf("Unknowns: %d\n", blanks[0]);
    printf("Simplifying the puzlle solutions\n");
    simplify();
    if(blanks[0]==0)  //Early win.   Sometimes the simplify fuction actualy solves.
    {
        drawPuzzle();
        exit(0);
    }
    printf("Optimizing solve order.\n");
    optOrder();
    printf("Begining bruit force solver\n");
    if (solve() == 1)
    {
        drawPuzzle();
    }
    else
    {
        printf("No soultion\n");
    }
}







