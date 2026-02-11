Java_magick_MagickImage_averageImages
  (JNIEnv *env, jobject self)
{
    Image *image, *average;
    ExceptionInfo exception;
    jobject newObj;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Cannot retrieve image handle");
	return NULL;
    }

    GetExceptionInfo(&exception);
    average = AverageImages(image, &exception);
    if (average == NULL) {
        throwMagickApiException(env, "Failed to create average image",
                                &exception);
        DestroyExceptionInfo(&exception);
        return NULL;
    }
    DestroyExceptionInfo(&exception);

    newObj = newImageObject(env, average);
    if (newObj == NULL) {
        DestroyImages(average);
        throwMagickException(env, "Unable to create average image");
        return NULL;
    }
    return newObj;
}
