gf_cli3_1_log_rotate_cbk (struct rpc_req *req, struct iovec *iov,
                          int count, void *myframe)
{
        gf_cli_rsp             rsp   = {0,};
        int                    ret   = -1;
        char                   msg[1024] = {0,};

        if (-1 == req->rpc_status) {
                goto out;
        }

        ret = xdr_to_generic (*iov, &rsp, (xdrproc_t)xdr_gf_cli_rsp);
        if (ret < 0) {
                gf_log ("", GF_LOG_ERROR, "error");
                goto out;
        }

        gf_log ("cli", GF_LOG_DEBUG, "Received resp to log rotate");

        if (rsp.op_ret && strcmp (rsp.op_errstr, ""))
                snprintf (msg, sizeof (msg), "%s", rsp.op_errstr);
        else
                snprintf (msg, sizeof (msg), "log rotate %s",
                          (rsp.op_ret) ? "unsuccessful": "successful");

#if (HAVE_LIB_XML)
        if (global_state->mode & GLUSTER_MODE_XML) {
                ret = cli_xml_output_str ("volLogRotate", msg, rsp.op_ret,
                                          rsp.op_errno, rsp.op_errstr);
                if (ret)
                        gf_log ("cli", GF_LOG_ERROR,
                                "Error outputting to xml");
                goto out;
        }
#endif

        if (rsp.op_ret)
                cli_err ("%s", msg);
        else
                cli_out ("%s", msg);
        ret = rsp.op_ret;

out:
        cli_cmd_broadcast_response (ret);
        if (rsp.dict.dict_val)
                free (rsp.dict.dict_val);

        return ret;
}
