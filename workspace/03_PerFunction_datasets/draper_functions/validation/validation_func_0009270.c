do_undef( void)


{
    DEFBUF *    defp;
    int     c;

    if ((c = skip_ws()) == '\n') {
        cerror( no_ident, NULL, 0L, NULL);
        unget_ch();
        return;
    }
    if (scan_token( c, (workp = work_buf, &workp), work_end) != NAM) {
        cerror( not_ident, work_buf, 0L, NULL);
        skip_nl();
        unget_ch();
    } else {
        if ((defp = look_id( identifier)) == NULL) {
            if (warn_level & 8)
                cwarn( "\"%s\" wasn't defined"
                        , identifier, 0L, NULL);
        } else if (standard && (defp->nargs <= DEF_NOARGS_STANDARD

                    || defp->nargs == DEF_PRAGMA)) {

            cerror( "\"%s\" shouldn't be undefined"
                    , identifier, 0L, NULL);
        } else if (standard) {
            c = skip_ws();
            unget_ch();
            if (c != '\n')
                return;
            else
                undefine( identifier);
        } else {
            undefine( identifier);
        }
    }
}
