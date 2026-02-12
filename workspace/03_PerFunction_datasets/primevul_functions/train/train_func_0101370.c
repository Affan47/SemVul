static bool define_smacro(Context *ctx, const char *mname, bool casesense,
                          int nparam, Token *expansion)
{
    SMacro *smac, **smhead;
    struct hash_table *smtbl;

    if (smacro_defined(ctx, mname, nparam, &smac, casesense)) {
        if (!smac) {
            nasm_error(ERR_WARNING|ERR_PASS1,
                  "single-line macro `%s' defined both with and"
                  " without parameters", mname);


            free_tlist(expansion);
            return false;
        } else {


            nasm_free(smac->name);
            free_tlist(smac->expansion);
        }
    } else {
        smtbl  = ctx ? &ctx->localmac : &smacros;
        smhead = (SMacro **) hash_findi_add(smtbl, mname);
        smac = nasm_malloc(sizeof(SMacro));
        smac->next = *smhead;
        *smhead = smac;
    }
    smac->name = nasm_strdup(mname);
    smac->casesense = casesense;
    smac->nparam = nparam;
    smac->expansion = expansion;
    smac->in_progress = false;
    return true;
}
