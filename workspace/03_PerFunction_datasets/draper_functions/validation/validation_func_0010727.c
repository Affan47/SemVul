copyall (uae_u8 *src, uae_u8 *dst, int pwidth, int pheight)
{
    int y;

    picasso_vidinfo.rowbytes = pwidth * g_amiga_video_bpp;

    if (picasso96_state.RGBFormat == host_mode) {

        int w = pwidth * picasso_vidinfo.pixbytes;
        for (y = 0; y < pheight; y++) {
            memcpy (dst, src, w);
            dst += picasso_vidinfo.rowbytes;
            src += picasso96_state.BytesPerRow;
        }
    }
    else {

        for (y = 0; y < pheight; y++)
            copyrow (src, dst, 0, y, pwidth);
    }


}
