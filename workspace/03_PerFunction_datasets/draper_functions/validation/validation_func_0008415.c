PerlFilter(value)
  BOOL value ;
{
    dSP;
    char *argv[] = { NULL };

    ENTER ;
    SAVETMPS ;


    if (PerlFilterActive && !value) {
        if (perl_get_cv("filter_end", FALSE) != NULL) {
            perl_call_argv("filter_end", G_EVAL|G_DISCARD|G_NOARGS, argv);
            if (SvTRUE(ERRSV))      {
                syslog (L_ERROR,"%s perl function filter_end died: %s",
                        LogName, SvPV(ERRSV, PL_na)) ;
                POPs ;
            }
        } else {
            PerlFilterActive = value ;
            LogPerl () ;
        }
    } else if (!PerlFilterActive && value) {
        if (perl_filter_cv == NULL) {
            syslog (L_ERROR,"%s perl filter not defined", LogName) ;
        } else {
            PerlFilterActive = value ;
            LogPerl () ;
        }
    }

    FREETMPS ;
    LEAVE ;
}
