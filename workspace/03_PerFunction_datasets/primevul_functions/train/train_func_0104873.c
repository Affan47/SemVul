static Token *pp_tokline(void)
{
    while (true) {
        Line *l = istk->expansion;
        Token *tline = NULL;
        Token *dtline;


        tline = NULL;
        while (l && l->finishes) {
            MMacro *fm = l->finishes;

            nasm_assert(fm == istk->mstk.mstk);

            if (!fm->name && fm->in_progress > 1) {


                fm->in_progress--;
                list_for_each(l, fm->expansion) {
                    Line *ll;

                    nasm_new(ll);
                    ll->next  = istk->expansion;
                    ll->first = dup_tlist(l->first, NULL);
                    ll->where = l->where;
                    istk->expansion = ll;
                }
                break;
            } else {
                MMacro *m = istk->mstk.mstk;


                if (defining) {
                    if (defining->name)
                        nasm_panic("defining with name in expansion");
                    else if (m->name)
                        nasm_fatal("`%%rep' without `%%endrep' within"
				   " expansion of macro `%s'", m->name);
                }


                istk->mstk = m->mstk;
                if (m->name) {


                    if (!--mmacro_deadman.levels) {


                        nasm_zero(mmacro_deadman);
                    }

#if 0
                    if (m->prev) {
                        pop_mmacro(m);
                        fm->in_progress --;
                    } else
#endif
                    {
                        nasm_free(m->params);
                        free_tlist(m->iline);
                        nasm_free(m->paramlen);
                        fm->in_progress = 0;
                    }
                }

                if (fm->nolist & NL_LIST) {
                    istk->nolist--;
                } else if (!istk->nolist) {
                    lfmt->downlevel(LIST_MACRO);
                }

                if (fm->nolist & NL_LINE) {
                    istk->noline--;
                } else if (!istk->noline) {
                    if (fm == src_macro_current())
                        src_macro_pop();
                    src_update(l->where);
                }

                istk->where = l->where;


#if 0
                else
                    free_mmacro(m);
#endif
            }
            istk->expansion = l->next;
            nasm_free(l);

            return &tok_pop;
        }

        do {
            char *line;

            if (istk->expansion) {
                Line *l = istk->expansion;

                istk->expansion = l->next;
                istk->where = l->where;
                tline = l->first;
                nasm_free(l);

                if (!istk->noline)
                    src_update(istk->where);

                if (!istk->nolist) {
                    line = detoken(tline, false);
                    lfmt->line(LIST_MACRO, istk->where.lineno, line);
                    nasm_free(line);
                }
            } else if ((line = read_line())) {
                line = prepreproc(line);
                tline = tokenize(line);
                nasm_free(line);
            } else {


                Include *i = istk;
                Include *is;

                if (i->fp)
                    fclose(i->fp);
                if (i->conds) {

                    nasm_fatal("expected `%%endif' before end of file");
                }

                list_for_each(is, i->next) {
                    if (is->fp) {
                        lfmt->downlevel(LIST_INCLUDE);
                        src_update(is->where);
                        break;
                    }
                }
                istk = i->next;
                nasm_free(i);
                return &tok_pop;
            }
        } while (0);


        if (!defining &&
            !(istk->conds && !emitting(istk->conds->state)) &&
            !(istk->mstk.mmac && !istk->mstk.mmac->in_progress)) {
            tline = expand_mmac_params(tline);
        }


        if (do_directive(tline, &dtline) == DIRECTIVE_FOUND) {
            if (dtline)
                return dtline;
        } else if (defining) {


            MMacro *mmac = defining->dstk.mmac;
            Line *l;

            nasm_new(l);
            l->next = defining->expansion;
            l->first = tline;
            l->finishes = NULL;
            l->where = istk->where;
            defining->expansion = l;


            if (mmac) {
                const Token *t;
                list_for_each(t, tline) {
                    if (!memcmp(t->text.a, "%00", 4))
                        mmac->capture_label = true;
                }
            }
        } else if (istk->conds && !emitting(istk->conds->state)) {


            free_tlist(tline);
        } else if (istk->mstk.mstk && !istk->mstk.mstk->in_progress) {


            free_tlist(tline);
        } else {
            tline = expand_smacro(tline);
            if (!expand_mmacro(tline))
                return tline;
        }
    }
}
