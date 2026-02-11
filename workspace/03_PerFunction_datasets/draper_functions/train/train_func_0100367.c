client3_1_rchecksum (call_frame_t *frame, xlator_t *this,
                     void *data)
{
        clnt_args_t        *args     = NULL;
        int64_t             remote_fd = -1;
        clnt_conf_t        *conf     = NULL;
        gfs3_rchecksum_req  req      = {0,};
        int                 op_errno = ESTALE;
        int                 ret        = 0;

        if (!frame || !this || !data)
                goto unwind;

        args = data;
        conf = this->private;

        CLIENT_GET_REMOTE_FD(conf, args->fd, remote_fd, unwind);

        req.len    = args->len;
        req.offset = args->offset;
        req.fd     = remote_fd;

        ret = client_submit_request (this, &req, frame, conf->fops,
                                     GFS3_OP_RCHECKSUM,
                                     client3_1_rchecksum_cbk, NULL,
                                     NULL, 0, NULL,
                                     0, NULL, (xdrproc_t)xdr_gfs3_rchecksum_req);
        if (ret) {
                op_errno = ENOTCONN;
                goto unwind;
        }

        return 0;
unwind:
        gf_log (this->name, GF_LOG_WARNING, "failed to send the fop: %s", strerror (op_errno));
        STACK_UNWIND_STRICT (rchecksum, frame, -1, op_errno, 0, NULL);
        return 0;
}
