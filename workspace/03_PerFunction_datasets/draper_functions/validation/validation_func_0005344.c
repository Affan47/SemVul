glusterd3_1_friend_update_cbk (struct rpc_req *req, struct iovec *iov,
                              int count, void *myframe)
{
        int                           ret    = -1;
        gd1_mgmt_friend_update_rsp    rsp    = {{0}, };
        xlator_t                      *this  = NULL;

        GF_ASSERT (req);
        this = THIS;

        if (-1 == req->rpc_status) {
                gf_log (this->name, GF_LOG_ERROR, "RPC Error");
                goto out;
        }

        ret = xdr_to_generic (*iov, &rsp,
                              (xdrproc_t)xdr_gd1_mgmt_friend_update_rsp);
        if (ret < 0) {
                gf_log (this->name, GF_LOG_ERROR, "Failed to serialize friend"
                        " update repsonse");
                goto out;
        }

        ret = 0;
out:
        gf_log (this->name, GF_LOG_INFO, "Received %s from uuid: %s",
                (ret)?"RJT":"ACC", uuid_utoa (rsp.uuid));

        GLUSTERD_STACK_DESTROY (((call_frame_t *)myframe));
        return ret;
}
