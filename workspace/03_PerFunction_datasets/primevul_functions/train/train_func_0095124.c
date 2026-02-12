sixel_dither_set_palette(
    sixel_dither_t  *dither,
    unsigned char   *palette)
{
    memcpy(dither->palette, palette, (size_t)(dither->ncolors * 3));
}
