re_reset(re_context *ctx)
{
    int i;


    for (i = 0 ; i < ctx->next_state ; ++i)
    {
        if (ctx->tuple_arr[i].char_range != 0)
        {
            mchfre(ctx->tuple_arr[i].char_range);
            ctx->tuple_arr[i].char_range = 0;
        }
    }


    ctx->next_state = RE_STATE_FIRST_VALID;


    ctx->cur_group = 0;
}
