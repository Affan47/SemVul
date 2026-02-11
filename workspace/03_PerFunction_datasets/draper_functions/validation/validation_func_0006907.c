do_all_sub(char *line, struct session *ses)
{
    struct listnode *ln;
    pvars_t vars,*lastpvars;
    char result[BUFFER_SIZE],tmp1[BUFFER_SIZE],tmp2[BUFFER_SIZE],*l;
    int rlen,len;

    lastpvars=pvars;
    pvars=&vars;

    ln = ses->subs;

    while ((ln = ln->next))
        if (check_one_action(line, ln->left, &vars, 0, ses))
        {
            if (!strcmp(ln->right, EMPTY_LINE))
            {
                strcpy(line, EMPTY_LINE);
                return;
            };
            substitute_vars(ln->right, tmp1);
            substitute_myvars(tmp1, tmp2, ses);
            rlen=match_start-line;
            memcpy(result, line, rlen);
            len=strlen(tmp2);
            APPEND(tmp2);
            while (*match_end)
                if (check_one_action(l=match_end, ln->left, &vars, 1, ses))
                {

                    len=match_start-l;
                    APPEND(l);
                    substitute_vars(ln->right, tmp1);
                    substitute_myvars(tmp1, tmp2, ses);
                    len=strlen(tmp2);
                    APPEND(tmp2);
                }
                else
                {
                    len=strlen(l);
                    APPEND(l);
                    break;
                }
            memcpy(line, result, rlen);
            line[rlen]=0;
        }

    pvars=lastpvars;
}
