test_read_with_filters(hid_t file)
{
    hid_t	dset;


#ifdef H5_HAVE_FILTER_DEFLATE
    TESTING("Testing deflate filter");

    if(H5Zfilter_avail(H5Z_FILTER_DEFLATE) != TRUE) TEST_ERROR

    if((dset = H5Dopen2(file,DSET_DEFLATE_NAME,H5P_DEFAULT)) < 0) TEST_ERROR

    if(test_read_data(dset, (int *)points_deflate) < 0) TEST_ERROR

    if(H5Dclose(dset) < 0) TEST_ERROR


#else
    TESTING("deflate filter");
    SKIPPED();
    puts("    Deflate filter not enabled");
#endif


    TESTING("Testing DYNLIB1 filter");

    if((dset = H5Dopen2(file,DSET_DYNLIB1_NAME,H5P_DEFAULT)) < 0) TEST_ERROR

    if(test_read_data(dset, (int *)points_dynlib1) < 0) TEST_ERROR

    if(H5Dclose(dset) < 0) TEST_ERROR


    TESTING("Testing DYNLIB2 filter");

    if((dset = H5Dopen2(file,DSET_DYNLIB2_NAME,H5P_DEFAULT)) < 0) TEST_ERROR

    if(test_read_data(dset, (int *)points_dynlib2) < 0) TEST_ERROR

    if(H5Dclose(dset) < 0) TEST_ERROR

    return 0;

error:
    return -1;
}
