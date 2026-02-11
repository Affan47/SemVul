distmin(int x0, int y0, int x1, int y1)
{
    register int dx = x0 - x1, dy = y0 - y1;
    if (dx < 0)
    {
        dx = -dx;
    }
    if (dy < 0)
    {
        dy = -dy;
    }


    return (dx < dy) ? dy : dx;
}
