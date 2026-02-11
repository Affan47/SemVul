glusterd_do_gsync_log_rotation_mst_slv (glusterd_volinfo_t *volinfo, char *slave,
                                        char **op_errstr)
{
        uuid_t           uuid = {0, };
        glusterd_conf_t *priv = NULL;
        int              ret  = 0;
        char errmsg[1024] = {0,};

        GF_ASSERT (volinfo);
        GF_ASSERT (slave);
        GF_ASSERT (THIS);
        GF_ASSERT (THIS->private);

        priv = THIS->private;

        ret = glusterd_gsync_get_uuid (slave, volinfo, uuid);
        if ((ret == 0) && (uuid_compare (priv->uuid, uuid) != 0))
                goto out;

        if (ret) {
                snprintf(errmsg, sizeof(errmsg), "geo-replication session b/w %s %s not active",
                         volinfo->volname, slave);
                gf_log ("", GF_LOG_WARNING, errmsg);
                if (op_errstr)
                        *op_errstr = gf_strdup(errmsg);
                goto out;
        }

        ret = glusterd_do_gsync_log_rotate (volinfo->volname, slave, &uuid, op_errstr);

 out:
        gf_log ("", GF_LOG_DEBUG, "Returning with %d", ret);
        return ret;
}
