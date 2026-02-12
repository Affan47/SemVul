static SMacro *define_smacro(const char *mname, bool casesense,
                             Token *expansion, SMacro *tmpl)
{
    SMacro *smac, **smhead;
    struct hash_table *smtbl;
    Context *ctx;
    bool defining_alias = false;
    int nparam = 0;
    bool defined;

    if (tmpl) {
        defining_alias = tmpl->alias;
        nparam = tmpl->nparam;
        if (nparam && !defining_alias)
            mark_smac_params(expansion, tmpl, 0);
    }

    ctx = get_ctx(mname, &mname);

    defined = smacro_defined(ctx, mname, nparam, &smac, casesense, true);

    if (defined) {
        if (smac->alias) {
            if (smac->in_progress) {
                nasm_nonfatal("macro alias loop");
                goto fail;
            }

            if (!defining_alias && !ppopt.noaliases) {

                SMacro *s;

                smac->in_progress = true;
                s = define_smacro(tok_text(smac->expansion), casesense,
                                  expansion, tmpl);
                smac->in_progress = false;
                return s;
            }
        }

        if (casesense ^ smac->casesense) {


            nasm_warn(WARN_MACRO_DEF_CASE_SINGLE, "case %ssensitive definition of macro `%s' will shadow %ssensitive macro `%s'",
                      casesense ? "" : "in",
                      mname,
                      smac->casesense ? "" : "in",
                      smac->name);
            defined = false;
        } else if ((!!nparam) ^ (!!smac->nparam)) {


            nasm_warn(WARN_MACRO_DEF_PARAM_SINGLE,
                      "macro `%s' defined both with and without parameters",
                      mname);
            defined = false;
        } else if (smac->nparam < nparam) {


            nasm_warn(WARN_MACRO_DEF_GREEDY_SINGLE,
                      "defining macro `%s' shadows previous greedy definition",
                      mname);
            defined = false;
        }
    }

    if (defined) {


        clear_smacro(smac);
    } else {

        smtbl  = ctx ? &ctx->localmac : &smacros;
        smhead = (SMacro **) hash_findi_add(smtbl, mname);
        nasm_new(smac);
        smac->next = *smhead;
        *smhead = smac;
    }

    smac->name      = nasm_strdup(mname);
    smac->casesense = casesense;
    smac->expansion = expansion;
    smac->expand    = smacro_expand_default;
    if (tmpl) {
        smac->nparam     = tmpl->nparam;
        smac->params     = tmpl->params;
        smac->alias      = tmpl->alias;
        smac->greedy     = tmpl->greedy;
        if (tmpl->expand)
            smac->expand = tmpl->expand;
    }
    if (list_option('s')) {
        list_smacro_def((smac->alias ? PP_DEFALIAS : PP_DEFINE)
                        + !casesense, ctx, smac);
    }
    return smac;

fail:
    free_tlist(expansion);
    if (tmpl)
        free_smacro_members(tmpl);
    return NULL;
}
