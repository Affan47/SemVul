rc_ctx_init(regcomp_ctx *ctx, ScmRegexp *rx)
{
    ctx->rx = rx;
    ctx->pattern = (SCM_FALSEP(rx->pattern)? rx->ast : rx->pattern);
    ctx->casefoldp = FALSE;
    ctx->lookbehindp = FALSE;
    if (SCM_STRINGP(rx->pattern)) {
        ctx->ipat = SCM_PORT(Scm_MakeInputStringPort(SCM_STRING(rx->pattern),
                                                     FALSE));
    } else {
        ctx->ipat = NULL;
    }
    ctx->sets = SCM_NIL;
    ctx->grpcount = 0;
    ctx->code = NULL;
    ctx->codep = 0;
    ctx->emitp = FALSE;
    ctx->codemax = 1;
}
