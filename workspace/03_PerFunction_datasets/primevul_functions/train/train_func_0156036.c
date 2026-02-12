ImagingNewEpilogue(Imaging im)
{


    if (!im->destroy)
        return (Imaging) ImagingError_MemoryError();


    switch (im->pixelsize) {
    case 1: case 2: case 3:
        im->image8 = (UINT8 **) im->image;
        break;
    case 4:
        im->image32 = (INT32 **) im->image;
        break;
    }

    return im;
}
