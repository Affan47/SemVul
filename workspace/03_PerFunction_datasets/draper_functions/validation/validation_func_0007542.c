create_stype3(void)
{
    hid_t   array_dt1, tid;
    const hsize_t	eight = 8;


    if((array_dt1 = H5Tarray_create2(H5T_NATIVE_INT,1, &eight)) < 0)
        goto error;

    if((tid = H5Tcreate(H5T_COMPOUND, sizeof(stype3))) < 0 ||
            H5Tinsert(tid, "a", HOFFSET(stype3, a), H5T_NATIVE_INT) < 0 ||
            H5Tinsert(tid, "b", HOFFSET(stype3, b), H5T_NATIVE_INT) < 0 ||
            H5Tinsert(tid, "c", HOFFSET(stype3, c), array_dt1) < 0 ||
            H5Tinsert(tid, "d", HOFFSET(stype3, d), H5T_NATIVE_INT) < 0 ||
            H5Tinsert(tid, "e", HOFFSET(stype3, e), H5T_NATIVE_INT) < 0)
        goto error;

    if(H5Tclose(array_dt1) < 0)
        goto error;

    return tid;

error:
    return FAIL;
}
