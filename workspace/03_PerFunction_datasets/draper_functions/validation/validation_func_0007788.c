art_pdf_knockoutisolated_group_8(byte *dst, const byte *src, int n_chan)
{
    byte src_alpha;

    src_alpha = src[n_chan];
    if (src_alpha == 0)
        return;

    memcpy (dst, src, n_chan + 1);
}
