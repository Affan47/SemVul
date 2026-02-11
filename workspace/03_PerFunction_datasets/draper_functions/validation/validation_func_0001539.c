H5D_term_interface(void)
{
    int	n = 0;

    FUNC_ENTER_NOAPI_NOINIT_NOERR

    if(H5_interface_initialize_g) {
	if(H5I_nmembers(H5I_DATASET) > 0) {


	    (void)H5I_clear_type(H5I_DATASET, TRUE, FALSE);
            n++;
	}
        else {

            n += H5D__term_pub_interface();


            n += H5D__term_deprec_interface();


	    (void)H5I_dec_type_ref(H5I_DATASET);
            n++;


	    H5_interface_initialize_g = 0;
	}
    }

    FUNC_LEAVE_NOAPI(n)
}
