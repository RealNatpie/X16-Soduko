#define S_BCOLOR CH_GREEN
#define S_IBCOLOR CH_GRAY2

#include <stdio.h>
#include <ctype.h>
#include <conio.h>
#include <cx16.h>

const char TOPG[] = { S_BCOLOR,CH_ULCORNER,CH_HLINE,CH_HLINE,CH_HLINE,CH_HLINE,
    CH_HLINE,CH_TTEE,CH_HLINE,CH_HLINE,CH_HLINE,CH_HLINE,CH_HLINE,CH_TTEE,
    CH_HLINE,CH_HLINE,CH_HLINE,CH_HLINE,CH_HLINE,CH_URCORNER,0x00 };
    
    const char MIDL[] = { S_BCOLOR,CH_VLINE,S_IBCOLOR,0x20,CH_VLINE,0x20,CH_VLINE,0x20,
                          S_BCOLOR,CH_VLINE,
                         S_IBCOLOR,0x20,CH_VLINE,0x20,CH_VLINE,0x20,S_BCOLOR,CH_VLINE,
                         S_IBCOLOR,0x20,CH_VLINE,0x20,CH_VLINE,0x20,S_BCOLOR,
                         CH_VLINE,0x00 };
    const char MIDD[] = { S_BCOLOR, CH_VLINE,S_IBCOLOR,CH_HLINE,CH_CROSS,CH_HLINE,CH_CROSS,CH_HLINE,S_BCOLOR,CH_VLINE,
                        S_IBCOLOR,CH_HLINE,CH_CROSS,CH_HLINE,CH_CROSS,CH_HLINE,S_BCOLOR,CH_VLINE,
                        S_IBCOLOR,CH_HLINE,CH_CROSS,CH_HLINE,CH_CROSS,CH_HLINE,S_BCOLOR,CH_VLINE,0x00 };
    const char DVDR[] = { S_BCOLOR,CH_LTEE,CH_HLINE,CH_HLINE,CH_HLINE,CH_HLINE,CH_HLINE,CH_CROSS,
                        CH_HLINE,CH_HLINE,CH_HLINE,CH_HLINE,CH_HLINE,CH_CROSS,
                        CH_HLINE,CH_HLINE,CH_HLINE,CH_HLINE,CH_HLINE,CH_RTEE,0x00 };
    const char BTM[] = { S_BCOLOR,CH_LLCORNER,CH_HLINE,CH_HLINE,CH_HLINE,CH_HLINE,CH_HLINE,
                         CH_BTEE,CH_HLINE,CH_HLINE,CH_HLINE,CH_HLINE,CH_HLINE,
                         CH_BTEE,CH_HLINE,CH_HLINE,CH_HLINE,CH_HLINE,CH_HLINE,
                         CH_LRCORNER,CH_WHITE,0x00 };

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
void __fastcall__ exit(int status);
signed char __fastcall__ videomode(signed char Mode);
unsigned char __fastcall__ cursor(unsigned char onoff);
void __fastcall__ cbm_k_bsout(unsigned char C);
int getKeypress();
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
void main()
{
    long coplx;
    int cl;
    cbm_k_bsout(142);
    videomode(1);
    clrscr();
    splash();
    initLookup();
    printf("preare to enter puzzle.\n");
    inputPuz();
    printf("checking complexity\n");
    findBlanks();
    coplx = (long)blanks[0];
    for (cl = 0; cl<9;cl++)
    {
        coplx *= 9L;
    }
    printf("unknowns: %d complexity: %lld\n", blanks[0], coplx);
    printf("simplifying the puzlle solutions\n");
    simplify();
    if(blanks[0]==0)
    {
        drawPuzzle(0);
        exit(0);
    }
    printf("optimizing solve order\n");
    optOrder();
    printf("begining bruit force solver\n");
    if (solve() == 1)
    {
        drawPuzzle(0);
    }
    else
    {
        printf("no soultion\n");
    }
}

void splash()
{
    printf("soduko solver by nathanael nunes\n");
    printf("V1.1 build march 29 2025\n");

}
void initLookup()
{
    int i, idx, startRow, startCol, cellIndex;
    printf("generateing lookup tables.\n");
    for (i = 0; i < 81; i++)
    {
        AddCol[i] = i % 9;
        AddRow[i] = i / 9;
        AddCel[i] = AddCol[i] / 3 + (AddRow[i] / 3) * 3;
    }

    for (i = 0; i < 9; i++)
    {
        for (idx = 0; idx < 9; idx++)
        {
            colAdds[i][idx] = i + idx * 9;
            rowAdds[i][idx] = i * 9 + idx;
            startRow = (i / 3) * 3;
            startCol = (i % 3) * 3;
            cellIndex = startRow * 9 + startCol;
            celAdds[i][idx] = cellIndex + (idx / 3) * 9 + (idx % 3);
        }
    }
}
int testAdr(int ad, int v)
{
    int i;
    for (i = 0; i < 9; i++)
    {
        if (ad != colAdds[AddCol[ad]][i] && puzzle[colAdds[AddCol[ad]][i]] == v)
            return 0;
        if (ad != rowAdds[AddRow[ad]][i] && puzzle[rowAdds[AddRow[ad]][i]] == v)
            return 0;
        if (ad != celAdds[AddCel[ad]][i] && puzzle[celAdds[AddCel[ad]][i]] == v)
            return 0;
    }
    return 1;
}
void inputPuz()
{
    char c;
    int i;
    cursor(1);
    printf("please enter 1-9 or 0 for blank.  backspace to undo.\n");
    printf("*************************\n*");
    for (i = 0; i < 81;)
    {
gcst:
        c = getKeypress();
        if(c==10 && i > 0)
        {
            i--;
            clrscr();
            splash();
            printf("please enter 1-9 or 0 for blank.  backspace to undo.\n");
            drawPuzzle(i);
            goto gcst;
        }
        if (testAdr(i, c) > 0 || c == 0)
        {
            puzzle[i++] = c;
            if (c > 0)
            {
                printf(" %d", c);
            }
            else
            {
                printf("  ");
            }
            if (AddCol[i] % 3 == 0)
            {
                printf(" *");
            }
            if (AddCol[i] == 0)
            {
                printf("\n*");
                if (AddRow[i] % 3 == 0)
                {
                    printf("************************");
                    printf("\n*");
                }
            }
        }
    }
    cursor(0);
}

void drawPuzzle(int noc)

{
    int i;
    if(noc < 1 || noc > 81)
    {
        noc = 81;
    }
    printf("*************************\n*");
    for (i = 0; i < noc; i++)
    {
        if(puzzle[i]>0)
        {
            printf(" %d",puzzle[i]);
        }
        else
        {
            printf("  ");
        }
        if(AddCol[i+1] % 3 == 0)
        {
            printf(" *");
        }
        if(AddCol[i+1] == 0)
        {
            printf("\n*");
            if(AddRow[i+1] % 3 == 0)
            {
                printf("************************\n");
                if(i!=80)
                {
                    printf("*");
                }
            }
        }
    }
}
int getKeypress()
{
    int c;
    
    for (;;)
    {
        c = cgetc();
        if(c==3)
            exit(0);
        if(c==20)
            return 10;
        if (isdigit(c) > 0)
            return c - 48;;
    }
    return c - 48;
}
void findBlanks()
{
    int i;
    blanks[0] = 0;
    for (i = 0; i < 81; i++)
    {
        if (puzzle[i] == 0)
        {
            blanks[blanks[0] + 1] = i;
            blanks[0]++;
        }
    }
}
void simplify()
{
    int i, vals;
stlp:
    for (i = 0; i < blanks[0]; i++)
    {
        posBlanks[i][0] = 0;
        for (vals = 1; vals < 10; vals++)
        {
            if (testAdr(blanks[i + 1], vals) > 0)
            {
                posBlanks[i][posBlanks[i][0] + 1] = vals;
                posBlanks[i][0]++;
            }
        }
    }
    vals = 0;
    for (i = 0; i < blanks[0]; i++)
    {
        if (posBlanks[i][0] == 1)
        {
            vals = 1;
            break;
        }
    }
    showComp();
    if (vals == 1)
    {
        fillones();
        findBlanks();
        goto stlp;
    }
}
void fillones()
{
    int i;
    for (i = 0; i < blanks[0]; i++)
    {
        if (posBlanks[i][0] == 1)
        {
            puzzle[blanks[i + 1]] = posBlanks[i][1];
        }
    }
}
void showComp()
{
    int i;
    long cpx;
    cpx = 1L;
    for (i = 0; i < blanks[0]; i++)
    {
        cpx *= (long)posBlanks[i][0];
    }
    printf("Unknowns: %d Complexity: %d\n", blanks[0], cpx);
}
void optOrder()
{
    int idx, val, opnt;
    opnt = 0;
    for (val = 1; val < 10; val++)
    {
        for (idx = 0; idx < blanks[0]; idx++)
        {
            if (posBlanks[idx][0] == val)
            {
                slvOrder[opnt++] = idx;
            }
        }
    }
}
int solve()
{
    int sidx, cadd, endidx,idxPnt;
    int valpnt[81];
    int valptEnd;
    int dspcnt;
    long sltst;
    int tarval;
    dspcnt = 0;
    sltst = 0;;
    sidx = 0;
    endidx = blanks[0];
smlp:
    idxPnt = slvOrder[sidx];
    cadd = blanks[idxPnt + 1];
    valpnt[idxPnt] = 0;
    valptEnd = posBlanks[idxPnt][0];
mlp:
    dspcnt++;
    if(dspcnt==10000)
    {
        printf("%ld soultions tested\n",sltst);
        dspcnt = 0;
    }
    tarval = posBlanks[idxPnt][valpnt[idxPnt]+1];
    if (testAdr(cadd, tarval) > 0)
    {
        puzzle[cadd] = tarval;
        goto ntlp;
    }
    idxinc:
    valpnt[idxPnt]++;
    if (valpnt[idxPnt] == valptEnd)
    {
        goto prlp;
    }
    goto mlp;
ntlp:
    sidx++;
    if (sidx == endidx)
    {
        goto slvd;
    }
    goto smlp;
prlp:
    sltst++;
    if (sidx == 0)
    {
        goto fld;
    }
    puzzle[cadd] = 0;
    valpnt[slvOrder[sidx]] = 0;
    sidx--;
    cadd = blanks[slvOrder[sidx] + 1];
    valptEnd = posBlanks[slvOrder[sidx]][0];
    idxPnt = slvOrder[sidx];
    goto idxinc;
slvd:
    sltst++;
    printf("solution# %ld\n",sltst);
    return 1;
fld:
    return 0;
}

