EGifPutPixel(GifFileType * GifFile,
             GifPixelType Pixel) {

    GifFilePrivateType *Private = (GifFilePrivateType *)GifFile->Private;

    if (!IS_WRITEABLE(Private)) {

        _GifError = E_GIF_ERR_NOT_WRITEABLE;
        return GIF_ERROR;
    }

    if (Private->PixelCount == 0) {
        _GifError = E_GIF_ERR_DATA_TOO_BIG;
        return GIF_ERROR;
    }
    --Private->PixelCount;


    Pixel &= CodeMask[Private->BitsPerPixel];

    return EGifCompressLine(GifFile, &Pixel, 1);
}
