magic_scandesc_cleanup(cli_ctx *ctx, cli_file_t type, unsigned char *hash, size_t hashed_size, int cache_clean, int retcode, void *parent_property)
{
#if HAVE_JSON
    ctx->wrkproperty = (struct json_object *)(parent_property);
#else
    UNUSEDPARAM(parent_property);
#endif

    UNUSEDPARAM(type);

    cli_dbgmsg("cli_magic_scandesc: returning %d %s\n", retcode, __AT__);
    if(ctx->engine->cb_post_scan) {
        perf_start(ctx, PERFT_POSTCB);
        switch(ctx->engine->cb_post_scan(fmap_fd(*ctx->fmap), retcode, retcode == CL_VIRUS ? cli_get_last_virus(ctx) : NULL, ctx->cb_ctx)) {
        case CL_BREAK:
            cli_dbgmsg("cli_magic_scandesc: file whitelisted by post_scan callback\n");
            perf_stop(ctx, PERFT_POSTCB);
            return CL_CLEAN;
        case CL_VIRUS:
            cli_dbgmsg("cli_magic_scandesc: file blacklisted by post_scan callback\n");
            cli_append_virus(ctx, "Detected.By.Callback");
            perf_stop(ctx, PERFT_POSTCB);
            if (retcode != CL_VIRUS)
                return cli_checkfp(hash, hashed_size, ctx);
            return CL_VIRUS;
        case CL_CLEAN:
            break;
        default:
            cli_warnmsg("cli_magic_scandesc: ignoring bad return code from post_scan callback\n");
        }
        perf_stop(ctx, PERFT_POSTCB);
    }
    if (retcode == CL_CLEAN && cache_clean) {
        perf_start(ctx, PERFT_CACHE);
        cache_add(hash, hashed_size, ctx);
        perf_stop(ctx, PERFT_CACHE);
    }
    return retcode;
}
