DrawLaTeXPoint(FILE * pf, int i, int fPlayer, int c)
{

    int j, x, y = 0;

    if (i < 6)
        x = 320 - 20 * i;
    else if (i < 12)
        x = 300 - 20 * i;
    else if (i < 18)
        x = 20 * i - 160;
    else if (i < 24)
        x = 20 * i - 140;
    else if (i == 24)
        x = 200;
    else
        x = 365;

    if (fClockwise)
        x = 400 - x;

    for (j = 0; j < c; j++) {
        if (j == 5 || (i == 24 && j == 3)) {
            fprintf(pf, "\\whiten\\path(%d,%d)(%d,%d)(%d,%d)(%d,%d)(%d,%d)\n"
                    "\\path(%d,%d)(%d,%d)(%d,%d)(%d,%d)(%d,%d)\n"
                    "\\put(%d,%d){\\makebox(10,10){\\textsf{\\tiny %d}}}\n",
                    x - 5, y - 5, x + 5, y - 5, x + 5, y + 5, x - 5, y + 5,
                    x - 5, y - 5,
                    x - 5, y - 5, x + 5, y - 5, x + 5, y + 5, x - 5, y + 5, x - 5, y - 5, x - 5, y - 5, c);
            break;
        }

        if (i == 24)

            y = fPlayer ? 60 + 20 * j : 200 - 20 * j;
        else if (fPlayer)
            y = i < 12 || i == 25 ? 30 + 20 * j : 230 - 20 * j;
        else
            y = i >= 12 && i != 25 ? 30 + 20 * j : 230 - 20 * j;

        fprintf(pf, fPlayer ? "\\put(%d,%d){\\circle{10}}"
                "\\put(%d,%d){\\blacken\\circle{20}}\n" :
                "\\put(%d,%d){\\whiten\\circle{20}}" "\\put(%d,%d){\\circle{20}}\n", x, y, x, y);
    }
}
