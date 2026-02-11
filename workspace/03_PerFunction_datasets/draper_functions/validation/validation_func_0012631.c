test_sec2_h5repart_opens(void)
{
    hid_t       file=(-1);


    if((file=H5Fopen(FILENAME[2], H5F_ACC_RDWR, H5P_DEFAULT))<0)
        goto error;

    if(H5Fclose(file)<0)
        goto error;

    return 0;

error:
    H5E_BEGIN_TRY {
        H5Fclose(file);
    } H5E_END_TRY;
    return -1;
}
