glusterd_bricks_select_remove_brick (dict_t *dict, char **op_errstr,
                                     struct list_head *selected)
{
        int                                     ret = -1;
        char                                    *volname = NULL;
        glusterd_volinfo_t                      *volinfo = NULL;
        glusterd_brickinfo_t                    *brickinfo = NULL;
        char                                    *brick = NULL;
        int32_t                                 count = 0;
        int32_t                                 i = 1;
        char                                    key[256] = {0,};
        glusterd_pending_node_t                 *pending_node = NULL;
        int32_t                                 force = 0;


        ret = dict_get_str (dict, "volname", &volname);

        if (ret) {
                gf_log ("", GF_LOG_ERROR, "Unable to get volume name");
                goto out;
        }

        ret = glusterd_volinfo_find (volname, &volinfo);

        if (ret) {
                gf_log ("", GF_LOG_ERROR, "Unable to allocate memory");
                goto out;
        }

        ret = dict_get_int32 (dict, "count", &count);
        if (ret) {
                gf_log ("", GF_LOG_ERROR, "Unable to get count");
                goto out;
        }

        ret = dict_get_int32 (dict, "force", &force);
        if (ret) {
                gf_log (THIS->name, GF_LOG_INFO, "force flag is not set");
                ret = 0;
                goto out;
        }

        while ( i <= count) {
                snprintf (key, 256, "brick%d", i);
                ret = dict_get_str (dict, key, &brick);
                if (ret) {
                        gf_log ("glusterd", GF_LOG_ERROR, "Unable to get brick");
                        goto out;
                }

                ret = glusterd_volume_brickinfo_get_by_brick (brick, volinfo,
                                                              &brickinfo);
                if (ret)
                        goto out;
                if (glusterd_is_brick_started (brickinfo)) {
                        pending_node = GF_CALLOC (1, sizeof (*pending_node),
                                                  gf_gld_mt_pending_node_t);
                        if (!pending_node) {
                                ret = -1;
                                goto out;
                        } else {
                                pending_node->node = brickinfo;
                                pending_node->type = GD_NODE_BRICK;
                                list_add_tail (&pending_node->list, selected);
                                pending_node = NULL;
                        }
                }
                i++;
        }

out:
        return ret;
}
