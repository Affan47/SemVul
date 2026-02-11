test_dangle_group(H5F_close_degree_t degree)
{
    char	filename[1024];
    hid_t fid;
    hid_t fapl;
    hid_t gid;
    unsigned u;

    TESTING("    dangling group IDs");

    if(H5open() < 0)
        TEST_ERROR;


    if((fapl=H5Pcreate(H5P_FILE_ACCESS)) < 0)
        TEST_ERROR;


    if(H5Pset_fclose_degree(fapl,degree) < 0)
        TEST_ERROR;

    h5_fixname(FILENAME[0], H5P_DEFAULT, filename, sizeof filename);
    if((fid = H5Fcreate (filename, H5F_ACC_TRUNC, H5P_DEFAULT, fapl)) < 0)
        TEST_ERROR;

    if((gid = H5Gcreate2(fid, GROUPNAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT)) < 0) FAIL_STACK_ERROR

    if(H5Gclose(gid) < 0)
        TEST_ERROR;


    H5E_BEGIN_TRY {
        gid = H5Gcreate2(fid, GROUPNAME, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    } H5E_END_TRY;
    if(gid >= 0) TEST_ERROR


    for(u = 0; u < MAX_DANGLE; u++)
        if((gid = H5Gopen2(fid, GROUPNAME, H5P_DEFAULT)) < 0)
            FAIL_STACK_ERROR

    if((gid = H5Gopen2(fid, GROUPNAME, H5P_DEFAULT)) < 0)
        FAIL_STACK_ERROR

    if(degree==H5F_CLOSE_SEMI) {
        H5E_BEGIN_TRY {
            if(H5Fclose(fid)>=0)
                TEST_ERROR;
        } H5E_END_TRY;
    }
    else
        if(H5Fclose(fid) < 0)
            TEST_ERROR;

    if(h5_get_file_size(filename, fapl) < 0)
        TEST_ERROR;

    if(H5Pclose(fapl) < 0)
        TEST_ERROR;

    if(H5close() < 0)
        TEST_ERROR;


    HDremove(filename);

    PASSED();
    return 0;

error:
    return 1;
}
