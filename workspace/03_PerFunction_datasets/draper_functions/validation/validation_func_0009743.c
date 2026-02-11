nfs_inode_opendir (xlator_t *nfsx, xlator_t *xl, nfs_user_t *nfu, loc_t *loc,
                   fop_opendir_cbk_t cbk, void *local)
{
        struct nfs_fop_local    *nfl = NULL;
        fd_t                    *newfd = NULL;
        int                     ret = -EFAULT;

        if ((!nfsx) || (!xl) || (!loc) || (!nfu))
                return ret;

        newfd = fd_create (loc->inode, 0);
        if (!newfd) {
                gf_log (GF_NFS, GF_LOG_ERROR, "Failed to create fd");
                ret = -ENOMEM;
                goto err;
        }

        nfs_fop_handle_local_init (NULL, nfsx, nfl, cbk, local, ret, err);
        ret = nfs_fop_opendir (nfsx, xl, nfu, loc, newfd,
                               nfs_inode_opendir_cbk, nfl);

err:
        if (ret < 0) {
                if (newfd)
                        fd_unref (newfd);
                nfs_fop_local_wipe (xl, nfl);
        }

        return ret;
}
