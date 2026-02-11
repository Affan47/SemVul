glusterd_profile_volume_use_rsp_dict (dict_t *aggr, dict_t *rsp_dict)
{
        int     ret = 0;
        glusterd_pr_brick_rsp_conv_t rsp_ctx = {0};
        int32_t brick_count = 0;
        int32_t count = 0;
        dict_t  *ctx_dict = NULL;
        glusterd_op_t   op = GD_OP_NONE;

        GF_ASSERT (rsp_dict);

        ret = dict_get_int32 (rsp_dict, "count", &brick_count);
        if (ret) {
                ret = 0;
                goto out;
        }

        op = glusterd_op_get_op ();
        GF_ASSERT (GD_OP_PROFILE_VOLUME == op);
        if (aggr) {
                ctx_dict = aggr;

        } else {
                ctx_dict = glusterd_op_get_ctx ();
        }

        ret = dict_get_int32 (ctx_dict, "count", &count);
        rsp_ctx.count = count;
        rsp_ctx.dict = ctx_dict;
        dict_foreach (rsp_dict, _profile_volume_add_friend_rsp, &rsp_ctx);
        dict_del (ctx_dict, "count");
        ret = dict_set_int32 (ctx_dict, "count", count + brick_count);
out:
        return ret;
}
