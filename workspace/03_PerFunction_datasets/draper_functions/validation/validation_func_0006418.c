bifcvs(bifcxdef *ctx, int argc)
{
    char *p;
    int   len;
    char  buf[30];

    bifcntargs(ctx, 1, argc);
    switch(runtostyp(ctx->bifcxrun))
    {
    case DAT_NIL:
        p = "nil";
        len = 3;
        (void)runpoplog(ctx->bifcxrun);
        break;

    case DAT_TRUE:
        p = "true";
        len = 4;
        (void)runpoplog(ctx->bifcxrun);
        break;

    case DAT_NUMBER:
        sprintf(buf, "%ld", runpopnum(ctx->bifcxrun));
        p = buf;
        len = strlen(buf);
        break;

    case DAT_SSTRING:

        return;

    default:

        runsig1(ctx->bifcxrun, ERR_INVTBIF, ERRTSTR, "cvtstr");
    }

    runpstr(ctx->bifcxrun, p, len, 0);
}
