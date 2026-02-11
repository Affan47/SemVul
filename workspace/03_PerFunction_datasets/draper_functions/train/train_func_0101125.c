Java_sun_misc_Signal_findSignal(JNIEnv *env, jclass cls, jstring name)
{
    jint res;
    const char *cname = (*env)->GetStringUTFChars(env, name, 0);
    if (cname == NULL) {

        return 0;
    }
    res = JVM_FindSignal(cname);
    (*env)->ReleaseStringUTFChars(env, name, cname);
    return res;
}
