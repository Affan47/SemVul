Java_magick_DrawInfo_setTile
  (JNIEnv *env, jobject self, jobject tileImage)
{
    DrawInfo *drawInfo;
    Image *image, *imgCopy;
    ExceptionInfo exception;

    drawInfo = (DrawInfo*) getHandle(env, self, "drawInfoHandle", NULL);
    if (drawInfo == NULL) {
        throwMagickException(env, "Unable to obtain DrawInfo handle");
        return;
    }

    image = (Image*) getHandle(env, tileImage, "magickImageHandle", NULL);
    if (image == NULL) {
        throwMagickException(env, "Unable to obtain MagickImage handle");
        return;
    }

    GetExceptionInfo(&exception);
    imgCopy = CloneImage(image, 0, 0, 1, &exception);
    if (imgCopy == NULL) {
        throwMagickApiException(env, "Unable to clone MagickImage",
                                &exception);
        DestroyExceptionInfo(&exception);
        return;
    }
    DestroyExceptionInfo(&exception);

    if (drawInfo->tile != NULL) {
        DestroyImages(drawInfo->tile);
    }
    drawInfo->tile = imgCopy;
}
