PrintLaTeXBoard(FILE * pf, matchstate * pms, int fPlayer)
{

    int anOff[2] = { 15, 15 }, i, x, y;


    fprintf(pf, "\\bigskip\\pagebreak[1]\\begin{center}\\begin{picture}"
            "(356,240)(22,10)\n" "\\%sboard\n", fPlayer ? "black" : "white");

    for (i = 0; i < 25; i++) {
        anOff[0] -= pms->anBoard[0][i];
        anOff[1] -= pms->anBoard[1][i];

        DrawLaTeXPoint(pf, i, 0, pms->anBoard[!fPlayer][i]);
        DrawLaTeXPoint(pf, i, 1, pms->anBoard[fPlayer][i]);
    }

    DrawLaTeXPoint(pf, 25, 0, anOff[!fPlayer]);
    DrawLaTeXPoint(pf, 25, 1, anOff[fPlayer]);

    if (fClockwise)
        x = 365;
    else
        x = 35;

    if (pms->fCubeOwner < 0)
        y = 130;
    else if (pms->fCubeOwner)
        y = 30;
    else
        y = 230;

    fprintf(pf, "\\path(%d,%d)(%d,%d)(%d,%d)(%d,%d)(%d,%d)"
            "\\put(%d,%d){\\makebox(24,24){\\textsf{\\large %d}}}\n",
            x - 12, y - 12, x + 12, y - 12, x + 12, y + 12, x - 12, y + 12,
            x - 12, y - 12, x - 12, y - 12, pms->nCube == 1 ? 64 : pms->nCube);

    fputs("\\end{picture}\\end{center}\\vspace{-4mm}\n\n\\nopagebreak[4]\n", pf);
}
