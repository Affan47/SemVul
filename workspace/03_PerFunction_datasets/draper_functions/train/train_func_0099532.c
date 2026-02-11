I_Squash1x(int x1, int y1, int x2, int y2)
{
    byte *bufp, *screenp;
    int y;


    if (x1 != 0 || y1 != 0 || x2 != SCREENWIDTH || y2 != SCREENHEIGHT)
    {
        return false;
    }

    bufp = src_buffer;
    screenp = (byte *) dest_buffer;

    for (y=0; y<SCREENHEIGHT; ++y)
    {
        WriteSquashedLine1x(screenp, bufp);

        screenp += dest_pitch;
        bufp += SCREENWIDTH;
    }

    return true;
}
