void
Perl__invlist_dump(pTHX_ PerlIO *file, I32 level,
                         const char * const indent, SV* const invlist)
{


    UV start, end;
    STRLEN count = 0;

    PERL_ARGS_ASSERT__INVLIST_DUMP;

    if (invlist_is_iterating(invlist)) {
        Perl_dump_indent(aTHX_ level, file,
             "%sCan't dump inversion list because is in middle of iterating\n",
             indent);
        return;
    }

    invlist_iterinit(invlist);
    while (invlist_iternext(invlist, &start, &end)) {
	if (end == UV_MAX) {
	    Perl_dump_indent(aTHX_ level, file,
                                       "%s[%" UVuf "] 0x%04" UVXf " .. INFTY\n",
                                   indent, (UV)count, start);
	}
	else if (end != start) {
	    Perl_dump_indent(aTHX_ level, file,
                                    "%s[%" UVuf "] 0x%04" UVXf " .. 0x%04" UVXf "\n",
		                indent, (UV)count, start,         end);
	}
	else {
	    Perl_dump_indent(aTHX_ level, file, "%s[%" UVuf "] 0x%04" UVXf "\n",
                                            indent, (UV)count, start);
	}
        count += 2;
    }
}
