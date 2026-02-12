ImagingNewBlock(const char *mode, int xsize, int ysize)
{
    Imaging im;
    Py_ssize_t y, i;

    im = ImagingNewPrologue(mode, xsize, ysize);
    if (!im)
        return NULL;


    if (im->linesize &&
        im->ysize > INT_MAX / im->linesize) {

        return NULL;
    }

    if (im->ysize * im->linesize <= 0) {


        im->block = (char *) malloc(1);
    } else {

        im->block = (char *) calloc(im->ysize, im->linesize);
    }

    if (im->block) {
        for (y = i = 0; y < im->ysize; y++) {
            im->image[y] = im->block + i;
            i += im->linesize;
        }

        im->destroy = ImagingDestroyBlock;

    }

    return ImagingNewEpilogue(im);
}
