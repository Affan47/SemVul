server_rchecksum_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                      int32_t op_ret, int32_t op_errno,
                      uint32_t weak_checksum, uint8_t *strong_checksum)
{
        gfs3_rchecksum_rsp  rsp = {0,};
        rpcsvc_request_t   *req = NULL;
        server_state_t      *state = NULL;

        req           = frame->local;

        state = CALL_STATE(frame);
        rsp.op_ret    = op_ret;
        rsp.op_errno  = gf_errno_to_error (op_errno);

        if (op_ret >= 0) {
                rsp.weak_checksum = weak_checksum;

                rsp.strong_checksum.strong_checksum_val = (char *)strong_checksum;
                rsp.strong_checksum.strong_checksum_len = MD5_DIGEST_LEN;
        }
        if (op_ret == -1)
                gf_log (this->name, GF_LOG_INFO,
                        "%"PRId64": RCHECKSUM %"PRId64" (%s)==> %"PRId32" (%s)",
                        frame->root->unique, state->resolve.fd_no,
                        state->fd ? uuid_utoa (state->fd->inode->gfid) : "--",
                        op_ret, strerror (op_errno));

        server_submit_reply (frame, req, &rsp, NULL, 0, NULL,
                             (xdrproc_t)xdr_gfs3_rchecksum_rsp);

        return 0;
}
