nfs3_symlink_resume (void *carg)
{
        nfsstat3                        stat = NFS3ERR_SERVERFAULT;
        int                             ret = -EFAULT;
        nfs3_call_state_t               *cs = NULL;
        nfs_user_t                      nfu = {0, };

        if (!carg)
                return ret;

        cs = (nfs3_call_state_t *)carg;
        nfs3_check_new_fh_resolve_status (cs, stat, nfs3err);
        nfs_request_user_init (&nfu, cs->req);
        ret = nfs_symlink (cs->nfsx, cs->vol, &nfu, cs->pathname,
                           &cs->resolvedloc, nfs3svc_symlink_cbk, cs);
        if (ret < 0)
                stat = nfs3_errno_to_nfsstat3 (-ret);

nfs3err:
        if (ret < 0) {
                nfs3_log_common_res (rpcsvc_request_xid (cs->req),
                                     NFS3_SYMLINK, stat, -ret);
                nfs3_symlink_reply (cs->req, stat, NULL, NULL, NULL, NULL);
                nfs3_call_state_wipe (cs);
        }

        return ret;
}
