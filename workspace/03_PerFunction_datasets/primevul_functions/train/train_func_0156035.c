ImagingNew2(const char* mode, Imaging imOut, Imaging imIn)
{


    if (imOut) {

        if (strcmp(imOut->mode, mode) != 0
            || imOut->xsize != imIn->xsize
            || imOut->ysize != imIn->ysize) {
            return ImagingError_Mismatch();
        }
    } else {

        imOut = ImagingNew(mode, imIn->xsize, imIn->ysize);
        if (!imOut)
            return NULL;
    }

    return imOut;
}
