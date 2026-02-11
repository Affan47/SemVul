clist_VMerror_recover_flush(gx_device_clist_writer *cldev,
                            int old_error_code)
{
    int free_code = 0;
    int reset_code = 0;
    int code;


    if (!clist_test_VMerror_recoverable(cldev) ||
        old_error_code != gs_error_VMerror
        )
        return old_error_code;
    free_code = (*cldev->free_up_bandlist_memory)( (gx_device *)cldev, true );


    reset_code = clist_reset( (gx_device *)cldev );
    if (reset_code >= 0)
        reset_code = clist_open_output_file( (gx_device *)cldev );
    if ( reset_code >= 0 &&
         (cldev->disable_mask & clist_disable_pass_thru_params)
         )
        reset_code = clist_put_current_params(cldev);
    if (reset_code < 0) {
        cldev->permanent_error = reset_code;
        cldev->error_is_retryable = 0;
    }

    code = (reset_code < 0 ? reset_code : free_code < 0 ? old_error_code : 0);
    if_debug1m('L', cldev->memory, "[L]hard flush of command list, status: %d\n", code);
    return code;
}
