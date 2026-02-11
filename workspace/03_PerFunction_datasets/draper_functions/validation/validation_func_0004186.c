Java_magick_ImageInfo_setImageOption
    (JNIEnv *env, jobject self, jstring option, jstring value)
{
    ImageInfo *info = NULL;
    const char *cstr1 = NULL;
    const char *cstr2 = NULL;

    info = (ImageInfo *) getHandle(env, self, "imageInfoHandle", NULL);
    if (info == NULL) {
        throwMagickException(env, "Unable to retrieve handle");
        return;
    }

    cstr1 = (*env)->GetStringUTFChars(env, option, 0);
    if (cstr1 == NULL) {
        throwMagickException(env, "Unable to retrieve Java string chars");
        return;
    }

    cstr2 = (*env)->GetStringUTFChars(env, value, 0);
    if (cstr2 == NULL) {
        throwMagickException(env, "Unable to retrieve Java string chars");
        return;
    }

    SetImageOption(info, (char *)AcquireString(cstr1), (char *)AcquireString(cstr2));

    (*env)->ReleaseStringUTFChars(env, option, cstr1);
    (*env)->ReleaseStringUTFChars(env, value, cstr2);
}
