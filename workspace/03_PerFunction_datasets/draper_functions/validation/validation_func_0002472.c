gen_extlink_src(hid_t loc_id)
{
    hid_t gid=0;
    int status;
    herr_t ret = SUCCEED;


    gid = H5Gcreate2(loc_id, "/group_ext", H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    if (gid < 0)
    {
        fprintf(stderr, "Error: %s %d> H5Gcreate2 failed.\n", FUNC, __LINE__);
        ret = FAIL;
        goto out;
    }


    status = H5Lcreate_external(HDF_EXT_TRG_FILE, "/simple", gid, "extlink_dset", H5P_DEFAULT, H5P_DEFAULT);
    if (status < 0)
    {
        fprintf(stderr, "Error: %s %d> H5Lcreate_external failed.\n", FUNC, __LINE__);
        ret = FAIL;
        goto out;
    }


    status = H5Lcreate_external(HDF_EXT_TRG_FILE, "/group", gid, "extlink_grp", H5P_DEFAULT, H5P_DEFAULT);
    if (status < 0)
    {
        fprintf(stderr, "Error: %s %d> H5Lcreate_external failed.\n", FUNC, __LINE__);
        ret = FAIL;
        goto out;
    }


    status = H5Lcreate_external(HDF_EXT_TRG_FILE, "/datatype", gid, "extlink_datatype", H5P_DEFAULT, H5P_DEFAULT);
    if (status < 0)
    {
        fprintf(stderr, "Error: %s %d> H5Lcreate_external failed.\n", FUNC, __LINE__);
        ret = FAIL;
        goto out;
    }


    status = H5Lcreate_external(HDF_EXT_TRG_FILE, "notyet", gid, "extlink_notyet1", H5P_DEFAULT, H5P_DEFAULT);
    if (status < 0)
    {
        fprintf(stderr, "Error: %s %d> H5Lcreate_external failed.\n", FUNC, __LINE__);
        ret = FAIL;
        goto out;
    }


    status = H5Lcreate_external("notyet_file.h5", "notyet", gid, "extlink_notyet2", H5P_DEFAULT, H5P_DEFAULT);
    if (status < 0)
    {
        fprintf(stderr, "Error: %s %d> H5Lcreate_external failed.\n", FUNC, __LINE__);
        ret = FAIL;
        goto out;
    }

out:
    if(gid > 0)
        H5Gclose(gid);

    return ret;
}
