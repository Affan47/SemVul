xf86GetPixFormat(ScrnInfoPtr pScrn, int depth)
{
    int i;
    static PixmapFormatRec format;


    if (!formatsDone) {
        if (depth == 24) {
            Pix24Flags pix24 = Pix24DontCare;

            format.depth = 24;
            format.scanlinePad = BITMAP_SCANLINE_PAD;
            if (xf86Info.pixmap24 != Pix24DontCare)
                pix24 = xf86Info.pixmap24;
            else if (pScrn->pixmap24 != Pix24DontCare)
                pix24 = pScrn->pixmap24;
            if (pix24 == Pix24Use24)
                format.bitsPerPixel = 24;
            else
                format.bitsPerPixel = 32;
            return &format;
        }
    }

    for (i = 0; i < numFormats; i++)
        if (formats[i].depth == depth)
            break;
    if (i != numFormats)
        return &formats[i];
    else if (!formatsDone) {

        for (i = 0; i < pScrn->numFormats; i++)
            if (pScrn->formats[i].depth == depth)
                break;
        if (i != pScrn->numFormats)
            return &pScrn->formats[i];
    }
    return NULL;
}
