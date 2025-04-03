#include "soduko.h"
void inputPuz()
{
    char c;
    int i;
    printf("Please enter 1-9 or 0 for blank.  Youse Arrows and Backspace to Navigate\n");
    printf("Press enter to begin solving.");
    puzxLoc = wherex();
    puzyLoc = wherey();
    drawGrid(puzxLoc, puzyLoc);

    for (i = 0; i < 81;)
    {
    gcst:
        offsetCursor(puzxLoc, puzyLoc, i);
        c = getKeypress((puzzle[i] == 0) ? 0xA0 : puzzle[i] + 48);
        refillPuzzle(puzxLoc, puzyLoc);
        switch (c)
        {
        case CH_CURS_UP:
            if (i > 8)
                i -= 9;
            break;
        case CH_CURS_DOWN:
            if (i < 72)
                i += 9;
            break;
        case CH_CURS_LEFT:
            if (i > 0)
                i--;
            break;
        case CH_CURS_RIGHT:
            if (i < 80)
                i++;
            break;
        case CH_ENTER:
            refillPuzzle(puzxLoc, puzyLoc);
            gotoxy(0, puzyLoc + 20);
            return;
            break;
        }
        if (c == 10 && i > 0)
        {
            i--;
            puzzle[i] = 0;
            refillPuzzle(puzxLoc, puzyLoc);
            goto gcst;
        }
        if ((c < 10 && testAdr(i, c) > 0) || c == 0)
        {
            puzzle[i++] = c;
            if (c > 0)
            {
                cbm_k_chrout(c + 48);
            }

        }
    }
    gotoxy(0, puzyLoc + 20);
}
int getKeypress(char value)
{
    int c;
    int blinker;
    clock_t t_checked;
    t_checked = clock();
    blinker = 1;
    printf("\x12%c\x9D", value);//preinvert for quicker feedback
    for (;;)
    {
        while (kbhit() == 0)
        {
            if (clock() - t_checked > cursorTickTime)
            {
                t_checked = clock();
                if (blinker == 0)
                {
                    blinker = 1;
                    printf("\x12%c\x9D", value);
                }
                else
                {
                    blinker = 0;
                    printf("\x92%c\x9D", value);
                }
            }
        }
        printf("\x92 \x9D");
        c = cgetc();
        if (c == 3)
            exit(0);
        if (c == 20)
            return 10;
        if (isdigit(c) > 0)
            return c - 48;;
        if (c == CH_CURS_UP)
            return c;
        if (c == CH_CURS_DOWN)
            return c;
        if (c == CH_CURS_LEFT)
            return c;
        if (c == CH_CURS_RIGHT)
            return c;
        if (c == CH_ENTER)
            return c;

    }
    return c - 48;
}