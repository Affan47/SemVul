Java_magick_MagickImage_getFilter
  (JNIEnv *env, jobject self)
{
    Image *image = NULL;

    image = (Image*) getHandle(env, self, "magickImageHandle", NULL);
    if (image == NULL) {
	throwMagickException(env, "Unable to retrieve handle");
	return -1;
    }

    return image->filter;
}
