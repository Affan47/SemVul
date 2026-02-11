modperl_perl_global_restore(pTHX_ modperl_perl_globals_t *globals,
                                        modperl_perl_global_entry_t *entries)
{
    while (entries->name) {
        MP_dGLOBAL_PTR(globals, entries);

        switch (entries->type) {
          case MP_GLOBAL_AVCV:
            MP_PERL_GLOBAL_RESTORE(avcv, ptr);
            break;
          case MP_GLOBAL_GVHV:
            MP_PERL_GLOBAL_RESTORE(gvhv, ptr);
            break;
          case MP_GLOBAL_GVAV:
            MP_PERL_GLOBAL_RESTORE(gvav, ptr);
            break;
          case MP_GLOBAL_GVIO:
            MP_PERL_GLOBAL_RESTORE(gvio, ptr);
            break;
          case MP_GLOBAL_SVPV:
            MP_PERL_GLOBAL_RESTORE(svpv, ptr);
            break;
        }

        entries++;
    }
}
