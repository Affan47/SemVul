Java_ncsa_hdf_hdf5lib_H5_H5Tget_1member_1name
  (JNIEnv *env, jclass clss, jint type_id, jint field_idx)
{
    char *name;
    jstring str;

    name = H5Tget_member_name(type_id, field_idx);

    if (name == NULL) {
        return NULL;
    }


    str = ENVPTR->NewStringUTF(ENVPAR name);
    free(name);

    if (str == NULL)  {
        h5JNIFatalError(env,  "H5Tget_member_name:  returned string not created");
        return NULL;
    }

    return str;
}
