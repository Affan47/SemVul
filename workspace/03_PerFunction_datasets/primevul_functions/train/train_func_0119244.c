make_regexp(const char *s, long len, rb_encoding *enc, int flags, onig_errmsg_buffer err,
	const char *sourcefile, int sourceline)
{
    Regexp *rp;
    int r;
    OnigErrorInfo einfo;


    r = onig_new_with_source(&rp, (UChar*)s, (UChar*)(s + len), flags,
		 enc, OnigDefaultSyntax, &einfo, sourcefile, sourceline);
    if (r) {
	onig_error_code_to_str((UChar*)err, r, &einfo);
	return 0;
    }
    return rp;
}
