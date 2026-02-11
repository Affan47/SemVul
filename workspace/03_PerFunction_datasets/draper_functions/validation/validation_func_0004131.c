F_DrawMap34End (void)
{
    signed int  scrolled;
    int         x;
    patch_t*    p1;
    patch_t*    p2;

    p1 = W_CacheLumpName (DEH_String("credit"),  PU_LEVEL);
    p2 = W_CacheLumpName (DEH_String("vellogo"), PU_LEVEL);

    V_MarkRect (0, 0, SCREENWIDTH, SCREENHEIGHT);


    scrolled = (320 - ((signed int) finalecount-430)/2);
    if (scrolled > 320)
        scrolled = 320;
    if (scrolled < 0)
        scrolled = 0;

#ifdef STRIFE_DEMO_CODE
    for ( x=0 ; x<SCREENWIDTH ; x++)
    {
        if (x+scrolled < 320)
            F_DrawPatchCol (x, p1, x+scrolled);
        else
            F_DrawPatchCol (x, p2, x+scrolled - 320);
    }
#else

    x = 1;
    do
    {
        x += 11;
    }
    while(x < 320);
#endif
}
