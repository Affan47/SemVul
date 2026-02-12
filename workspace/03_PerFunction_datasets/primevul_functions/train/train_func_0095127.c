sixel_dither_set_transparent(
    sixel_dither_t  *dither,
    int             transparent)
{
    dither->keycolor = transparent;
}
