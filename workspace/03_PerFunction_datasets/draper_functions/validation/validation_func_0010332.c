glusterd_is_valid_volfpath (char *volname, char *brick)
{
        char                    volfpath[PATH_MAX] = {0,};
        glusterd_brickinfo_t    *brickinfo = NULL;
        glusterd_volinfo_t      *volinfo = NULL;
        int32_t                 ret = 0;
        xlator_t                *this = NULL;

        this = THIS;
        GF_ASSERT (this);

        ret = glusterd_brickinfo_new_from_brick (brick, &brickinfo);
        if (ret) {
                gf_log (this->name, GF_LOG_WARNING, "Failed to create brickinfo"
                        " for brick %s", brick );
                ret = 0;
                goto out;
        }
        ret = glusterd_volinfo_new (&volinfo);
        if (ret) {
                gf_log (this->name, GF_LOG_WARNING, "Failed to create volinfo");
                ret = 0;
                goto out;
        }
        strncpy (volinfo->volname, volname, sizeof (volinfo->volname));
        get_brick_filepath (volfpath, volinfo, brickinfo);

        ret = (strlen (volfpath) < _POSIX_PATH_MAX);

out:
        if (brickinfo)
                glusterd_brickinfo_delete (brickinfo);
        if (volinfo)
                glusterd_volinfo_delete (volinfo);
        return ret;
}
