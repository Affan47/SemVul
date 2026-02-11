nfs3svc_access (rpcsvc_request_t *req)
{
        struct nfs3_fh  fh = {{0}, };
        access3args     args;
        int             ret = RPCSVC_ACTOR_ERROR;

        if (!req)
                return ret;

        nfs3_prep_access3args (&args, &fh);
        if (xdr_to_access3args (req->msg[0], &args) <= 0) {
                gf_log (GF_NFS3, GF_LOG_ERROR, "Error decoding args");
                rpcsvc_request_seterr (req, GARBAGE_ARGS);
                goto rpcerr;
        }

        ret = nfs3_access (req, &fh, args.access);
        if ((ret < 0) && (ret != RPCSVC_ACTOR_IGNORE)) {
                gf_log (GF_NFS3, GF_LOG_ERROR, "ACCESS procedure failed");
                rpcsvc_request_seterr (req, SYSTEM_ERR);
                ret = RPCSVC_ACTOR_ERROR;
        }

rpcerr:
        return ret;
}
