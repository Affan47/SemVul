ImagingNewArray(const char *mode, int xsize, int ysize)
{
    Imaging im;
    ImagingSectionCookie cookie;

    int y;
    char* p;

    im = ImagingNewPrologue(mode, xsize, ysize);
    if (!im)
        return NULL;

    ImagingSectionEnter(&cookie);


    for (y = 0; y < im->ysize; y++) {

        p = (char *) calloc(1, im->linesize);
        if (!p) {
            ImagingDestroyArray(im);
            break;
        }
        im->image[y] = p;
    }

    ImagingSectionLeave(&cookie);

    if (y == im->ysize)
        im->destroy = ImagingDestroyArray;

    return ImagingNewEpilogue(im);
}
