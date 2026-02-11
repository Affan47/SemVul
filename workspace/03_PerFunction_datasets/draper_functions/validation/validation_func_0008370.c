callJNIWrapperRefReturn(Class *class, MethodBlock *mb,
                                uintptr_t *ostack) {
    uintptr_t *ret;

    TRACE("<DLL: Calling JNI method %s.%s%s>\n", CLASS_CB(class)->name,
          mb->name, mb->type);

    if(!initJNILrefs())
        return NULL;

    ret = callJNIMethod(&jni_env,
                        (mb->access_flags & ACC_STATIC) ? class : NULL,
                        mb->simple_sig, mb->native_extra_arg, ostack,
                        mb->code, mb->args_count);

    *ostack = (uintptr_t)REF_TO_OBJ(*ostack);
    return ret;
}
