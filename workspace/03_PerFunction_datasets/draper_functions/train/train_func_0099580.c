H5D_get_space(H5D_t *dset)
{
    H5S_t	*space = NULL;
    hid_t       ret_value = FAIL;

    FUNC_ENTER_NOAPI_NOINIT


    if(NULL == (space = H5S_copy(dset->shared->space, FALSE, TRUE)))
        HGOTO_ERROR(H5E_DATASET, H5E_CANTINIT, FAIL, "unable to get data space")


    if((ret_value = H5I_register(H5I_DATASPACE, space, TRUE)) < 0)
        HGOTO_ERROR(H5E_ATOM, H5E_CANTREGISTER, FAIL, "unable to register dataspace")

done:
    if(ret_value < 0)
        if(space != NULL)
            if(H5S_close(space) < 0)
                HDONE_ERROR(H5E_DATASET, H5E_CLOSEERROR, FAIL, "unable to release dataspace")

    FUNC_LEAVE_NOAPI(ret_value)
}
