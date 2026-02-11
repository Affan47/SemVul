glusterfs_pidfile_cleanup (glusterfs_ctx_t *ctx)
{
        cmd_args_t      *cmd_args = NULL;

        cmd_args = &ctx->cmd_args;

        if (!ctx->pidfp)
                return 0;

        gf_log ("glusterfsd", GF_LOG_TRACE,
                "pidfile %s cleanup",
                cmd_args->pid_file);

        if (ctx->cmd_args.pid_file) {
                unlink (ctx->cmd_args.pid_file);
                ctx->cmd_args.pid_file = NULL;
        }

        lockf (fileno (ctx->pidfp), F_ULOCK, 0);
        fclose (ctx->pidfp);
        ctx->pidfp = NULL;

        return 0;
}
