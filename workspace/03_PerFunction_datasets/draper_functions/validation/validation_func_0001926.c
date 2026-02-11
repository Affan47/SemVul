mgmt_cbk_spec (void *data)
{
        glusterfs_ctx_t *ctx = NULL;

        ctx = glusterfs_ctx_get ();
        gf_log ("mgmt", GF_LOG_INFO, "Volume file changed");

        glusterfs_volfile_fetch (ctx);
        return 0;
}
