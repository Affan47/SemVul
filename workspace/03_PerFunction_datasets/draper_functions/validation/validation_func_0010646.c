mnt3_check_client_net (struct mount3_state *ms, rpcsvc_request_t *req,
                       xlator_t *targetxl)
{

        rpcsvc_t        *svc = NULL;
        int             ret = -1;

        if ((!ms) || (!req) || (!targetxl))
                return -1;

        svc = rpcsvc_request_service (req);
        ret = rpcsvc_transport_peer_check (svc->options, targetxl->name,
                                           rpcsvc_request_transport (req));
        if (ret == RPCSVC_AUTH_REJECT) {
                gf_log (GF_MNT, GF_LOG_TRACE, "Peer not allowed");
                goto err;
        }

        ret = rpcsvc_transport_privport_check (svc, targetxl->name,
                                               rpcsvc_request_transport (req));
        if (ret == RPCSVC_AUTH_REJECT) {
                gf_log (GF_MNT, GF_LOG_TRACE, "Unprivileged port not allowed");
                goto err;
        }

        ret = 0;
err:
        return ret;
}
