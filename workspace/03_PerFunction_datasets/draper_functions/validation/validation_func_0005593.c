fn_equal(fs_query *q, fs_value a, fs_value b)
{
#if 0
fs_value_print(a);
printf(" = ");
fs_value_print(b);
printf("\n");
#endif
    if (a.valid & fs_valid_bit(FS_V_TYPE_ERROR)) {
	return a;
    }
    if (b.valid & fs_valid_bit(FS_V_TYPE_ERROR)) {
	return b;
    }

    fs_value term_equal = fn_rdfterm_equal(q, a, b);
    if (term_equal.in == 1) {
        return term_equal;
    }

    if (a.attr == fs_c.xsd_datetime)
        return fn_datetime_equal(q, a, b);
    if (fs_is_numeric(&a) && fs_is_numeric(&b))
        return fn_numeric_equal(q, a, b);

    if (FS_IS_LITERAL(a.rid) && FS_IS_LITERAL(b.rid) &&
        (a.attr == fs_c.empty || a.attr == fs_c.xsd_string) &&
        (b.attr == fs_c.empty || b.attr == fs_c.xsd_string)) {
        return fs_value_boolean(!strcmp(a.lex, b.lex));
    }

    return fs_value_boolean(0);
}
