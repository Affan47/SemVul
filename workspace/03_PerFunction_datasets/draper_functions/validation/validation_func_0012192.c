glusterd_op_modify_op_ctx (glusterd_op_t op)
{
        int             ret = -1;
        dict_t          *op_ctx = NULL;
        int             brick_index_max = -1;
        int             other_count = 0;
        int             count = 0;
        uint32_t        cmd = GF_CLI_STATUS_NONE;

        op_ctx = glusterd_op_get_ctx();
        if (!op_ctx) {
                gf_log (THIS->name, GF_LOG_CRITICAL,
                        "Operation context is not present.");
                goto out;
        }

        switch (op) {
        case GD_OP_STATUS_VOLUME:
                ret = dict_get_uint32 (op_ctx, "cmd", &cmd);
                if (ret) {
                        gf_log (THIS->name, GF_LOG_DEBUG,
                                "Failed to get status cmd");
                        goto out;
                }
                if (!(cmd & GF_CLI_STATUS_NFS || cmd & GF_CLI_STATUS_SHD ||
                    (cmd & GF_CLI_STATUS_MASK) == GF_CLI_STATUS_NONE)) {
                        gf_log (THIS->name, GF_LOG_INFO,
                                "op_ctx modification not required for status "
                                "operation being performed");
                        goto out;
                }

                ret = dict_get_int32 (op_ctx, "brick-index-max",
                                      &brick_index_max);
                if (ret) {
                        gf_log (THIS->name, GF_LOG_DEBUG,
                                "Failed to get brick-index-max");
                        goto out;
                }

                ret = dict_get_int32 (op_ctx, "other-count", &other_count);
                if (ret) {
                        gf_log (THIS->name, GF_LOG_DEBUG,
                                "Failed to get other-count");
                        goto out;
                }

                count = brick_index_max + other_count + 1;

                ret = glusterd_op_volume_dict_uuid_to_hostname (op_ctx,
                                                                "brick%d.path",
                                                                0, count);
                if (ret)
                        gf_log (THIS->name, GF_LOG_WARNING,
                                "Failed uuid to hostname conversion");

                break;

        case GD_OP_PROFILE_VOLUME:
                ret = dict_get_str_boolean (op_ctx, "nfs", _gf_false);
                if (!ret)
                        goto out;

                ret = dict_get_int32 (op_ctx, "count", &count);
                if (ret) {
                        gf_log (THIS->name, GF_LOG_DEBUG,
                                "Failed to get brick count");
                        goto out;
                }

                ret = glusterd_op_volume_dict_uuid_to_hostname (op_ctx,
                                                                "%d-brick",
                                                                1, (count + 1));
                if (ret)
                        gf_log (THIS->name, GF_LOG_WARNING,
                                "Failed uuid to hostname conversion");

                break;


        case GD_OP_DEFRAG_BRICK_VOLUME:
                ret = dict_get_int32 (op_ctx, "count", &count);
                if (ret) {
                        gf_log (THIS->name, GF_LOG_DEBUG,
                                "Failed to get count");
                        goto out;
                }

                ret = glusterd_op_volume_dict_uuid_to_hostname (op_ctx,
                                                                "node-uuid-%d",
                                                                1, (count + 1));
                if (ret)
                        gf_log (THIS->name, GF_LOG_WARNING,
                                "Failed uuid to hostname conversion");
                break;

        default:
                ret = 0;
                gf_log (THIS->name, GF_LOG_INFO,
                        "op_ctx modification not required");
                break;

        }

out:
        if (ret)
                gf_log (THIS->name, GF_LOG_WARNING,
                        "op_ctx modification failed");
        return;
}
