globexp2(const Char *ptr, const Char *pattern, glob_t *pglob,
         struct glob_lim *limitp, int recursion)
{
    int         i, rv;
    Char       *lm, *ls;
    const Char *pe, *pm, *pl;
    Char        patbuf[PATH_MAX];


    for (lm = patbuf, pm = pattern; pm != ptr; *lm++ = *pm++)
        ;
    *lm = EOS;
    ls = lm;


    for (i = 0, pe = ++ptr; *pe; pe++) {
        if (*pe == LBRACKET) {

            for (pm = pe++; *pe != RBRACKET && *pe != EOS; pe++)
                ;
            if (*pe == EOS) {


                pe = pm;
            }
        } else if (*pe == LBRACE) {
            i++;
        } else if (*pe == RBRACE) {
            if (i == 0) {
                break;
            }
            i--;
        }
    }


    if (i != 0 || *pe == EOS) {
        return glob0(patbuf, pglob, limitp);
    }
    for (i = 0, pl = pm = ptr; pm <= pe; pm++) {
        switch (*pm) {
        case LBRACKET:

            for (pl = pm++; *pm != RBRACKET && *pm != EOS; pm++)
                ;
            if (*pm == EOS) {


                pm = pl;
            }
            break;

        case LBRACE:
            i++;
            break;

        case RBRACE:
            if (i) {
                i--;
                break;
            }

        case COMMA:
            if (i && *pm == COMMA) {
                break;
            } else {

                for (lm = ls; (pl < pm); *lm++ = *pl++)
                    ;


                for (pl = pe + 1; (*lm++ = *pl++) != EOS; )
                    ;


                rv = globexp1(patbuf, pglob, limitp, recursion + 1);
                if (rv && rv != GLOB_NOMATCH) {
                    return rv;
                }

                pl = pm + 1;
            }
            break;

        default:
            break;
        }
    }
    return 0;
}
