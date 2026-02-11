PointArea(const int fClockwise, const int nSize, const int n, int *px, int *py, int *pcx, int *pcy)
{


    int c_chequer = (n == 0 || n == 25) ? 3 : 5;

    *px = positions[fClockwise][n][0] * nSize;
    *py = positions[fClockwise][n][1] * nSize;
    *pcx = CHEQUER_WIDTH * nSize;
    *pcy = positions[fClockwise][n][2] * nSize;

    if (*pcy > 0) {
        *pcy = *pcy * (c_chequer - 1) + (CHEQUER_HEIGHT + DISPLAY_POINT_EXTRA) * nSize;
        *py += CHEQUER_HEIGHT * nSize - *pcy;
    } else
        *pcy = -*pcy * (c_chequer - 1) + (CHEQUER_HEIGHT + DISPLAY_POINT_EXTRA) * nSize;
}
