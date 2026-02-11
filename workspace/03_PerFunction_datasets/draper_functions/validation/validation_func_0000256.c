findWayUp (const int eI, const int eJ)
{
    int i, k;
    i = k = eI;


    Flags leftOK  = (dFlag [LEFT] | dFlag [STAND]);
    Flags rightOK = (dFlag [RIGHT] | dFlag [STAND]);

    if (grid->enemyMoves (eI, eJ) & dFlag [UP]) {
        return UP;
    }
    else {
        while ((i >= 0) || (k <= FIELDWIDTH)) {
            if (i >= 0) {
                if (grid->enemyMoves (i, eJ) & dFlag [UP]) {
                    return LEFT;
                }
                else if ((grid->enemyMoves (i--, eJ) & leftOK) != leftOK) {
                    i = -1;
                }
            }
            if (k <= FIELDWIDTH) {
                if (grid->enemyMoves (k, eJ) & dFlag [UP]) {
                    return RIGHT;
                }
                else if ((grid->enemyMoves (k++, eJ) & rightOK) != rightOK) {
                    k = FIELDWIDTH + 1;
                }
            }
        }
    }
    return STAND;
}
