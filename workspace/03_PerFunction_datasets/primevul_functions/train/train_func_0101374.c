static char *pp_getline(void)
{
    char *line;
    Token *tline;

    real_verror = nasm_set_verror(pp_verror);

    while (1) {


        tline = NULL;
        while (istk->expansion && istk->expansion->finishes) {
            Line *l = istk->expansion;
            if (!l->finishes->name && l->finishes->in_progress > 1) {
                Line *ll;


                l->finishes->in_progress--;
                list_for_each(l, l->finishes->expansion) {
                    Token *t, *tt, **tail;

                    ll = nasm_malloc(sizeof(Line));
                    ll->next = istk->expansion;
                    ll->finishes = NULL;
                    ll->first = NULL;
                    tail = &ll->first;

                    list_for_each(t, l->first) {
                        if (t->text || t->type == TOK_WHITESPACE) {
                            tt = *tail = new_Token(NULL, t->type, t->text, 0);
                            tail = &tt->next;
                        }
                    }

                    istk->expansion = ll;
                }
            } else {


                if (defining) {
                    if (defining->name)
                        nasm_panic(0, "defining with name in expansion");
                    else if (istk->mstk->name)
                        nasm_fatal(0, "`%%rep' without `%%endrep' within"
				   " expansion of macro `%s'",
				   istk->mstk->name);
                }


                {
                    MMacro *m = istk->mstk;
                    istk->mstk = m->next_active;
                    if (m->name) {


                        if (m->prev) {
                            pop_mmacro(m);
                            l->finishes->in_progress --;
                        } else {
                            nasm_free(m->params);
                            free_tlist(m->iline);
                            nasm_free(m->paramlen);
                            l->finishes->in_progress = 0;
                        }
                    }


#if 0
                    else
                        free_mmacro(m);
#endif
                }
                istk->expansion = l->next;
                nasm_free(l);
                lfmt->downlevel(LIST_MACRO);
            }
        }
        while (1) {

            if (istk->expansion) {
                char *p;
                Line *l = istk->expansion;
                if (istk->mstk)
                    istk->mstk->lineno++;
                tline = l->first;
                istk->expansion = l->next;
                nasm_free(l);
                p = detoken(tline, false);
                lfmt->line(LIST_MACRO, p);
                nasm_free(p);
                break;
            }
            line = read_line();
            if (line) {
                line = prepreproc(line);
                tline = tokenize(line);
                nasm_free(line);
                break;
            }


            {
                Include *i = istk;
                fclose(i->fp);
                if (i->conds) {

                    nasm_fatal(0,
                               "expected `%%endif' before end of file");
                }

                if (i->next)
                    src_set(i->lineno, i->fname);
                istk = i->next;
                lfmt->downlevel(LIST_INCLUDE);
                nasm_free(i);
                if (!istk) {
		    line = NULL;
		    goto done;
		}
                if (istk->expansion && istk->expansion->finishes)
                    break;
            }
        }


        if (!defining && !(istk->conds && !emitting(istk->conds->state))
            && !(istk->mstk && !istk->mstk->in_progress)) {
            tline = expand_mmac_params(tline);
        }


        if (do_directive(tline, &line) == DIRECTIVE_FOUND) {
            if (line)
                break;
            else
                continue;
        } else if (defining) {


            Line *l = nasm_malloc(sizeof(Line));
            l->next = defining->expansion;
            l->first = tline;
            l->finishes = NULL;
            defining->expansion = l;
            continue;
        } else if (istk->conds && !emitting(istk->conds->state)) {


            free_tlist(tline);
            continue;
        } else if (istk->mstk && !istk->mstk->in_progress) {


            free_tlist(tline);
            continue;
        } else {
            tline = expand_smacro(tline);
            if (!expand_mmacro(tline)) {


                line = detoken(tline, true);
                free_tlist(tline);
                break;
            } else {
                continue;
            }
        }
    }

done:
    nasm_set_verror(real_verror);
    return line;
}
