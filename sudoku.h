#ifndef SUDOKU_H
#define SUDOKU_H

#include <stdio.h>
#include <ctype.h>
#include <conio.h>
#include <time.h>
#include <cx16.h>

// Constants for colors
#define S_BCOLOR CH_GREEN
#define S_IBCOLOR CH_GRAY2

// Function prototypes
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
void drawGrid(int sx, int sy);
void refillPuzzle(int orx, int ory);
int testAdr(int ad, int v);
void __fastcall__ exit(int status);
signed char __fastcall__ videomode(signed char Mode);
unsigned char __fastcall__ cursor(unsigned char onoff);
void __fastcall__ cbm_k_bsout(unsigned char C);
void __fastcall__ gotoxy(unsigned char x, unsigned char y);
void __fastcall__ cputc(char c);
void __fastcall__ cbm_k_chrout(unsigned char C);
int getKeypress();

// Global variables
extern int puzzle[81];
extern int blanks[82];
extern int colAdds[9][9];
extern int rowAdds[9][9];
extern int celAdds[9][9];
extern int AddCol[81];
extern int AddRow[81];
extern int AddCel[81];
extern int posBlanks[81][10];
extern int slvOrder[81];
extern int puzxLoc, puzyLoc;
extern clock_t cursorTickTime;

// Grid drawing characters
extern const char TOPG[];
extern const char MIDL[];
extern const char MIDD[];
extern const char DVDR[];
extern const char BTM[];
extern const char VERNUM[];

#endif // SUDOKU_H
