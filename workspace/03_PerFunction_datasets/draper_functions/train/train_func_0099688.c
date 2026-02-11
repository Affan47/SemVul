glusterd_store_brickinfo (glusterd_volinfo_t *volinfo,
                          glusterd_brickinfo_t *brickinfo, int32_t brick_count,
                          int vol_fd)
{
        int32_t                 ret = -1;

        GF_ASSERT (volinfo);
        GF_ASSERT (brickinfo);

        ret = glusterd_store_volinfo_brick_fname_write (vol_fd, brickinfo,
                                                       brick_count);
        if (ret)
                goto out;

        ret = glusterd_store_create_brick_dir (volinfo);
        if (ret)
                goto out;

        ret = glusterd_store_create_brick_shandle_on_absence (volinfo,
                                                              brickinfo);
        if (ret)
                goto out;

        ret = glusterd_store_perform_brick_store (brickinfo);
out:
        gf_log ("", GF_LOG_DEBUG, "Returning with %d", ret);
        return ret;
}
