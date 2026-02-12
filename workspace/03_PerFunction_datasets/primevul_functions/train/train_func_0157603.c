S_invlist_contents(pTHX_ SV* const invlist, const bool traditional_style)
{


    UV start, end;
    SV* output;
    const char intra_range_delimiter = (traditional_style ? '\t' : '-');
    const char inter_range_delimiter = (traditional_style ? '\n' : ' ');

    if (traditional_style) {
        output = newSVpvs("\n");
    }
    else {
        output = newSVpvs("");
    }

    PERL_ARGS_ASSERT_INVLIST_CONTENTS;

    assert(! invlist_is_iterating(invlist));

    invlist_iterinit(invlist);
    while (invlist_iternext(invlist, &start, &end)) {
	if (end == UV_MAX) {
	    Perl_sv_catpvf(aTHX_ output, "%04" UVXf "%cINFINITY%c",
                                          start, intra_range_delimiter,
                                                 inter_range_delimiter);
	}
	else if (end != start) {
	    Perl_sv_catpvf(aTHX_ output, "%04" UVXf "%c%04" UVXf "%c",
		                          start,
                                                   intra_range_delimiter,
                                                  end, inter_range_delimiter);
	}
	else {
	    Perl_sv_catpvf(aTHX_ output, "%04" UVXf "%c",
                                          start, inter_range_delimiter);
	}
    }

    if (SvCUR(output) && ! traditional_style) {
        SvCUR_set(output, SvCUR(output) - 1);
    }

    return output;
}
