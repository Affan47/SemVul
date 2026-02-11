cloog_statement_get_fl(CloogStatement *s, int *f, int *l,
        CloogOptions *options)
{
    if (s == NULL) return;

    int fs, ls;

    if (options->fs != NULL && options->ls != NULL) {
        fs = options->fs[s->number-1];
        ls = options->ls[s->number-1];
        *f = (fs > *f)? fs: *f;
        *l = (ls > *l)? ls: *l;
    }else{
        *f = -1;
        *l = -1;
    }

    cloog_statement_get_fl(s->next, f, l, options);
}
