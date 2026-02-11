H5F_fake_free(H5F_t *f)
{
    FUNC_ENTER_NOAPI_NOINIT_NOERR


    if(f) {

        if(f->shared)
            f->shared = H5FL_FREE(H5F_file_t, f->shared);
        f = H5FL_FREE(H5F_t, f);
    }

    FUNC_LEAVE_NOAPI(SUCCEED)
}
