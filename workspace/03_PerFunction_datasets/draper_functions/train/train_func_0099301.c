Jam_CallVoidMethod(JNIEnv *env, jobject obj, jmethodID methodID, ...) {
    va_list jargs;
    MethodBlock *mb;
    Object *ob = REF_TO_OBJ(obj);

    va_start(jargs, methodID);
    if((mb = lookupVirtualMethod(ob, methodID)) != NULL)
        executeMethodVaList(ob, ob->class, mb, jargs);
    va_end(jargs);
}
