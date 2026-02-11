glfs_fini (struct glfs *fs)
{
        int             ret = -1;
        int             countdown = 100;
        xlator_t        *subvol = NULL;
        glusterfs_ctx_t *ctx = NULL;
        call_pool_t     *call_pool = NULL;

        ctx = fs->ctx;

        if (ctx->mgmt) {
                rpc_clnt_disable (ctx->mgmt);
                ctx->mgmt = NULL;
        }

        __glfs_entry_fs (fs);

        call_pool = fs->ctx->pool;

        while (countdown--) {

                if (!call_pool->cnt)
                        break;
                usleep (100000);
        }


        ret = (call_pool->cnt == 0)? 0: -1;

        subvol = glfs_active_subvol (fs);
        if (subvol) {


                xlator_notify (subvol, GF_EVENT_PARENT_DOWN, subvol, 0);


        }

        glfs_subvol_done (fs, subvol);

        return ret;
}
