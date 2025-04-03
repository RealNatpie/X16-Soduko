#include "soduko.h"
/*
#define S_BCOLOR CH_GREEN
#define S_IBCOLOR CH_GRAY2

#include <stdio.h>
#include <ctype.h>
#include <conio.h>
#include <time.h>
#include <cx16.h>
*/

/*
void splash();
void initLookup();
void inputPuz();
void drawPuzzle();
void findBlanks();
void simplify();
void fillones();
void showComp();
void optOrder();
int solve();
void offsetCursor(int ox, int oy, int cidx);
void __fastcall__ exit(int status);
signed char __fastcall__ videomode(signed char Mode);
unsigned char __fastcall__ cursor(unsigned char onoff);
void __fastcall__ cbm_k_bsout(unsigned char C);
void __fastcall__ gotoxy(unsigned char x, unsigned char y);
void __fastcall__ cputc(char c);
void __fastcall__ cbm_k_chrout(unsigned char C);
int getKeypress();
*/
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
    cursorTickTime = CLOCKS_PER_SEC / 4;
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
    if(blanks[0]==0)
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







