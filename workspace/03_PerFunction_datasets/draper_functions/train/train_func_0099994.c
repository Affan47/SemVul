H5FD_fapl_open(H5P_genplist_t *plist, hid_t driver_id, const void *driver_info)
{
    void *copied_driver_info = NULL;
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_NOAPI(FAIL)


    if(H5I_inc_ref(driver_id, FALSE) < 0)
        HGOTO_ERROR(H5E_FILE, H5E_CANTINC, FAIL, "unable to increment ref count on VFL driver")
    if(H5FD_fapl_copy(driver_id, driver_info, &copied_driver_info) < 0)
        HGOTO_ERROR(H5E_FILE, H5E_CANTCOPY, FAIL, "can't copy VFL driver info")


    if(H5P_set(plist, H5F_ACS_FILE_DRV_ID_NAME, &driver_id) < 0)
        HGOTO_ERROR(H5E_FILE, H5E_CANTSET, FAIL, "can't set driver ID")
    if(H5P_set(plist, H5F_ACS_FILE_DRV_INFO_NAME, &copied_driver_info) < 0)
        HGOTO_ERROR(H5E_FILE, H5E_CANTSET, FAIL, "can't set driver info")
    copied_driver_info = NULL;

done:
    if(ret_value < 0)
        if(copied_driver_info && H5FD_fapl_close(driver_id, copied_driver_info) < 0)
            HDONE_ERROR(H5E_FILE, H5E_CANTCLOSEOBJ, FAIL, "can't close copy of driver info")

    FUNC_LEAVE_NOAPI(ret_value)
}
