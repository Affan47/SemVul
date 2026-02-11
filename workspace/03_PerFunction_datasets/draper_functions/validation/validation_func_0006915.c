cr_poll_checkpoint_msg(cr_checkpoint_handle_t *handle, struct timeval *timeout, char **msg_p)
{
    int token = cri_chkpt_hndl_get_token(handle);
    int err;


    err = do_wait_fd(token, timeout);
    if (!err) {
	return 0;
    } else if (err < 0) {
#if HAVE_FTB
	if (errno != EINTR) {
	    my_log_error("CHKPT_ERROR");
	}
#endif
        return CR_POLL_CHKPT_ERR_PRE;
    }


    if (msg_p && (do_fetch_log(token, CR_OP_CHKPT_LOG, msg_p) < 0)) {
	return CR_POLL_CHKPT_ERR_LOG;
    }


    err = cr_reap_checkpoint(handle);
    return (err < 0) ? CR_POLL_CHKPT_ERR_POST : 1;
}
