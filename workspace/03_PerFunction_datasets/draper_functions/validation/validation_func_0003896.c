S_mg_free_struct(pTHX_ SV *sv, MAGIC *mg)
{
    const MGVTBL* const vtbl = mg->mg_virtual;
    if (vtbl && vtbl->svt_free)
	vtbl->svt_free(aTHX_ sv, mg);
    if (mg->mg_ptr && mg->mg_type != PERL_MAGIC_regex_global) {
	if (mg->mg_len > 0 || mg->mg_type == PERL_MAGIC_utf8)
	    Safefree(mg->mg_ptr);
	else if (mg->mg_len == HEf_SVKEY)
	    SvREFCNT_dec(MUTABLE_SV(mg->mg_ptr));
    }
    if (mg->mg_flags & MGf_REFCOUNTED)
	SvREFCNT_dec(mg->mg_obj);
    Safefree(mg);
}
