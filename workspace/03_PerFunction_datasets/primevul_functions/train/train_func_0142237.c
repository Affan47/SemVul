set_cinfo_polarity(gx_device * dev, gx_color_polarity_t new_polarity)
{
#ifdef DEBUG

    if (new_polarity == GX_CINFO_POLARITY_UNKNOWN) {
        dmprintf(dev->memory, "set_cinfo_polarity: illegal operand\n");
        return;
    }
#endif


    if (dev->color_info.polarity == GX_CINFO_POLARITY_UNKNOWN)
        dev->color_info.polarity = new_polarity;
}
