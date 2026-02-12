sixel_dither_unref(
    sixel_dither_t   *dither)
{

    if (dither != NULL && --dither->ref == 0) {
        sixel_dither_destroy(dither);
    }
}
