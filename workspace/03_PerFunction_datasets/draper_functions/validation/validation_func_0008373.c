glusterd_check_brick_rb_part (char *bricks, int count, glusterd_volinfo_t *volinfo)
{
        char                                    *saveptr = NULL;
        char                                    *brick = NULL;
        char                                    *brick_list = NULL;
        int                                     ret = 0;
        glusterd_brickinfo_t                    *brickinfo = NULL;
        uint32_t                                i = 0;
        char                                    *str = NULL;
        char                                    msg[2048] = {0,};

        brick_list = gf_strdup (bricks);
        if (!brick_list) {
                gf_log ("glusterd", GF_LOG_ERROR,
                        "Out of memory");
                ret = -1;
                goto out;
        }

        if (count)
                brick = strtok_r (brick_list+1, " \n", &saveptr);


        while ( i < count) {
                ret = glusterd_brickinfo_from_brick (brick, &brickinfo);
                if (ret) {
                        snprintf (msg, sizeof(msg), "Unable to"
                                  " get brickinfo");
                        gf_log ("", GF_LOG_ERROR, "%s", msg);
                        ret = -1;
                        goto out;
                }

                if (glusterd_is_replace_running (volinfo, brickinfo)) {
                        snprintf (msg, sizeof(msg), "Volume %s: replace brick is running"
                          " and the brick %s:%s you are trying to add is the destination brick"
                          " for replace brick", volinfo->volname, brickinfo->hostname, brickinfo->path);
                        ret = -1;
                        goto out;
                }

                glusterd_brickinfo_delete (brickinfo);
                brickinfo = NULL;
                brick = strtok_r (NULL, " \n", &saveptr);
                i++;
        }

out:
        if (brick_list)
                GF_FREE(brick_list);
        if (brickinfo)
                glusterd_brickinfo_delete (brickinfo);
        if (ret)
                str = gf_strdup (msg);
        return str;
}
