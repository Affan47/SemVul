H5FD_term_interface(void)
{
    int	n = 0;

    FUNC_ENTER_NOAPI_NOINIT_NOERR

    if(H5_interface_initialize_g) {
	if((n=H5I_nmembers(H5I_VFL))!=0) {
	    H5I_clear_type(H5I_VFL, FALSE, FALSE);


            if(H5I_nmembers(H5I_VFL)==0) {
                H5FD_sec2_term();
#ifdef H5_HAVE_DIRECT
                H5FD_direct_term();
#endif
                H5FD_log_term();
                H5FD_stdio_term();
#ifdef H5_HAVE_WINDOWS
                H5FD_windows_term();
#endif
                H5FD_family_term();
                H5FD_core_term();
                H5FD_multi_term();
#ifdef H5_HAVE_PARALLEL
                H5FD_mpio_term();
                H5FD_mpiposix_term();
#endif
            }
	} else {
	    H5I_dec_type_ref(H5I_VFL);
	    H5_interface_initialize_g = 0;
	    n = 1;
	}
    }
    FUNC_LEAVE_NOAPI(n)
}
