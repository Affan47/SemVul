Perl_av_delete(pTHX_ AV *av, I32 key, I32 flags)
{
    dVAR;
    SV *sv;

    PERL_ARGS_ASSERT_AV_DELETE;
    assert(SvTYPE(av) == SVt_PVAV);

    if (SvREADONLY(av))
	Perl_croak_no_modify();

    if (SvRMAGICAL(av)) {
        const MAGIC * const tied_magic
	    = mg_find((const SV *)av, PERL_MAGIC_tied);
        if ((tied_magic || mg_find((const SV *)av, PERL_MAGIC_regdata))) {
            SV **svp;
            if (key < 0) {
		if (!S_adjust_index(aTHX_ av, tied_magic, &key))
			return NULL;
            }
            svp = av_fetch(av, key, TRUE);
            if (svp) {
                sv = *svp;
                mg_clear(sv);
                if (mg_find(sv, PERL_MAGIC_tiedelem)) {
                    sv_unmagic(sv, PERL_MAGIC_tiedelem);
                    return sv;
                }
		return NULL;
            }
        }
    }

    if (key < 0) {
	key += AvFILL(av) + 1;
	if (key < 0)
	    return NULL;
    }

    if (key > AvFILLp(av))
	return NULL;
    else {
	if (!AvREAL(av) && AvREIFY(av))
	    av_reify(av);
	sv = AvARRAY(av)[key];
	if (key == AvFILLp(av)) {
	    AvARRAY(av)[key] = &PL_sv_undef;
	    do {
		AvFILLp(av)--;
	    } while (--key >= 0 && AvARRAY(av)[key] == &PL_sv_undef);
	}
	else
	    AvARRAY(av)[key] = &PL_sv_undef;
	if (SvSMAGICAL(av))
	    mg_set(MUTABLE_SV(av));
    }
    if (flags & G_DISCARD) {
	SvREFCNT_dec(sv);
	sv = NULL;
    }
    else if (AvREAL(av))
	sv = sv_2mortal(sv);
    return sv;
}
