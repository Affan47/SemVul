glob0(const Char *pattern, glob_t *pglob, struct glob_lim *limitp)
{
    const Char *qpatnext;
    int c, err, oldpathc;
    Char *bufnext, patbuf[PATH_MAX];

    qpatnext = pattern;
    oldpathc = pglob->gl_pathc;
    bufnext = patbuf;


    while ((c = *qpatnext++) != EOS) {
        switch (c) {
        case LBRACKET:
            c = *qpatnext;
            if (c == NOT) {
                ++qpatnext;
            }
            if (*qpatnext == EOS ||
                g_strchr(qpatnext + 1, RBRACKET) == NULL) {
                *bufnext++ = LBRACKET;
                if (c == NOT) {
                    --qpatnext;
                }
                break;
            }
            *bufnext++ = M_SET;
            if (c == NOT) {
                *bufnext++ = M_NOT;
            }
            c = *qpatnext++;
            do {
                *bufnext++ = CHAR(c);
                if (*qpatnext == RANGE &&
                    (c = qpatnext[1]) != RBRACKET) {
                    *bufnext++ = M_RNG;
                    *bufnext++ = CHAR(c);
                    qpatnext += 2;
                }
            } while ((c = *qpatnext++) != RBRACKET);
            pglob->gl_flags |= GLOB_MAGCHAR;
            *bufnext++ = M_END;
            break;
        case QUESTION:
            pglob->gl_flags |= GLOB_MAGCHAR;
            *bufnext++ = M_ONE;
            break;
        case STAR:
            pglob->gl_flags |= GLOB_MAGCHAR;


            if (bufnext == patbuf || bufnext[-1] != M_ALL) {
                *bufnext++ = M_ALL;
            }
            break;
        default:
            *bufnext++ = CHAR(c);
            break;
        }
    }
    *bufnext = EOS;

    if ((err = glob1(patbuf, patbuf+PATH_MAX - 1, pglob, limitp, 1)) != 0) {
        return err;
    }


    if (pglob->gl_pathc == oldpathc) {
        if ((pglob->gl_flags & GLOB_NOCHECK) ||
            ((pglob->gl_flags & GLOB_NOMAGIC) &&
                !(pglob->gl_flags & GLOB_MAGCHAR))) {
            return globextend(pattern, pglob, limitp, NULL);
        } else {
            return GLOB_NOMATCH;
        }
    }
    if (!(pglob->gl_flags & GLOB_NOSORT)) {
        if ((pglob->gl_flags & GLOB_KEEPSTAT)) {

            struct glob_path_stat *path_stat;
            int i;
            int n = pglob->gl_pathc - oldpathc;
            int o = pglob->gl_offs + oldpathc;

            if ((path_stat = calloc(n, sizeof(*path_stat))) == NULL) {
                return GLOB_NOSPACE;
            }
            for (i = 0; i < n; i++) {
                path_stat[i].gps_path = pglob->gl_pathv[o + i];
                path_stat[i].gps_stat = pglob->gl_statv[o + i];
            }
            qsort(path_stat, n, sizeof(*path_stat), compare_gps);
            for (i = 0; i < n; i++) {
                pglob->gl_pathv[o + i] = path_stat[i].gps_path;
                pglob->gl_statv[o + i] = path_stat[i].gps_stat;
            }
            free(path_stat);
        } else {
            qsort(pglob->gl_pathv + pglob->gl_offs + oldpathc,
                  pglob->gl_pathc - oldpathc, sizeof(char *),
                  compare);
        }
    }
    return 0;
}
