Java_ncsa_hdf_hdf5lib_H5_H5Pget_1cache
  (JNIEnv *env, jclass clss, jint plist, jintArray mdc_nelmts,
  jlongArray rdcc_nelmts, jlongArray rdcc_nbytes, jdoubleArray rdcc_w0)
{
    herr_t   status;
    jint     mode;
    jdouble *w0Array;
    jlong   *rdcc_nelmtsArray;
    jlong   *nbytesArray;
    jboolean isCopy;

    if (rdcc_w0 == NULL) {
        w0Array = (jdouble *)NULL;
    }
    else {
        w0Array = (jdouble *)ENVPTR->GetDoubleArrayElements(ENVPAR rdcc_w0, &isCopy);
        if (w0Array == NULL) {
            h5JNIFatalError(env, "H5Pget_cache:  w0_array array not pinned");
            return -1;
        }
    }

    if (rdcc_nelmts == NULL) {
        rdcc_nelmtsArray = (jlong *) NULL;
    }
    else {
        rdcc_nelmtsArray = (jlong *)ENVPTR->GetLongArrayElements(ENVPAR rdcc_nelmts, &isCopy);
        if (rdcc_nelmtsArray == NULL) {

            if (w0Array != NULL) {
                ENVPTR->ReleaseDoubleArrayElements(ENVPAR rdcc_w0, w0Array, JNI_ABORT);
            }
            h5JNIFatalError(env, "H5Pget_cache:  rdcc_nelmts array not pinned");
            return -1;
        }
    }

    if (rdcc_nbytes == NULL) {
        nbytesArray = (jlong *) NULL;
    }
    else {
        nbytesArray = (jlong *)ENVPTR->GetLongArrayElements(ENVPAR rdcc_nbytes, &isCopy);
        if (nbytesArray == NULL) {
            if (w0Array != NULL) {
                ENVPTR->ReleaseDoubleArrayElements(ENVPAR rdcc_w0, w0Array, JNI_ABORT);
            }
            if (rdcc_nelmtsArray != NULL) {
                ENVPTR->ReleaseLongArrayElements(ENVPAR rdcc_nelmts, rdcc_nelmtsArray, JNI_ABORT);
            }
            h5JNIFatalError(env, "H5Pget_cache:  nbytesArray array not pinned");
            return -1;
        }
    }
    {

        long long rdcc_nelmts_temp = *(rdcc_nelmtsArray);
        size_t rdcc_nelmts_t = (size_t)rdcc_nelmts_temp;
        long long nbytes_temp = *(nbytesArray);
        size_t nbytes_t = (size_t)nbytes_temp;

        status = H5Pget_cache((hid_t)plist, (int *)NULL, &rdcc_nelmts_t,
                &nbytes_t, (double *)w0Array);

        *rdcc_nelmtsArray = rdcc_nelmts_t;
        *nbytesArray = nbytes_t;
    }


    if (status < 0) {
        mode = JNI_ABORT;
    }
    else {
        mode = 0;
    }

    if (rdcc_nelmtsArray != NULL) {
        ENVPTR->ReleaseLongArrayElements(ENVPAR rdcc_nelmts, rdcc_nelmtsArray, mode);
    }

    if (nbytesArray != NULL) {
        ENVPTR->ReleaseLongArrayElements(ENVPAR rdcc_nbytes, nbytesArray, mode);
    }

    if (w0Array != NULL) {
        ENVPTR->ReleaseDoubleArrayElements(ENVPAR rdcc_w0, w0Array, mode);
    }

    if (status < 0) {
        h5libraryError(env);
    }

    return (jint)status;
}
