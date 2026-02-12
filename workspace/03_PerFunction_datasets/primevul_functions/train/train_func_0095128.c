sixel_dither_set_method_for_largest(
    sixel_dither_t   *dither,
    int              method_for_largest)
{
    if (method_for_largest == SIXEL_LARGE_AUTO) {
        method_for_largest = SIXEL_LARGE_NORM;
    }
    dither->method_for_largest = method_for_largest;
}
