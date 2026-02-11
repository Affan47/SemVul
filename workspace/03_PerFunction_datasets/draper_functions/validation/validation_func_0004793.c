Java_magick_MagickInfo_init
  (JNIEnv *env, jobject self, jstring modname)
{
    MagickInfo *magickInfo = NULL;
    jfieldID fid = 0;
    ExceptionInfo exception;
    const char *cstr = NULL;

    magickInfo = (MagickInfo*) getHandle(env, self, "magickInfoHandle", &fid);

    GetExceptionInfo(&exception);

    cstr = (*env)->GetStringUTFChars(env, modname, 0);
    if (cstr == NULL)
        return;

    magickInfo = (MagickInfo*) GetMagickInfo(cstr, &exception);


    (*env)->ReleaseStringUTFChars(env, modname, cstr);

    if (magickInfo == NULL) {
        throwMagickApiException(env, "Unable to read magick info", &exception);
        DestroyExceptionInfo(&exception);
        return;
    }
    DestroyExceptionInfo(&exception);

    setHandle(env, self, "magickInfoHandle", (void*) magickInfo, &fid);
}
