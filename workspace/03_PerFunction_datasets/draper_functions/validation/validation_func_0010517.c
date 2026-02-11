pack_warning(Octstr *packed, Octstr *value)
{
    long warn_code = -1;
    Octstr *warn_agent = NULL;
    Octstr *warn_text = NULL;
    long pos;
    long start;

    pos = octstr_parse_long(&warn_code, value, 0, 10);
    if (pos < 0 || warn_code < 0)
        goto error;

    if (warn_code > 99) {


	warn_code = convert_rfc2616_warning_to_rfc2068(warn_code);
    }

    if (warn_code > MAX_SHORT_INTEGER) {
	warning(0, "WSP: Cannot encode warning code %ld.", warn_code);
	return -1;
    }

    while (isspace(octstr_get_char(value, pos)))
        pos++;

    start = pos;
    while (pos < octstr_len(value) && !isspace(octstr_get_char(value, pos)))
        pos++;

    if (pos > start)
        warn_agent = octstr_copy(value, start, pos - start);

    while (isspace(octstr_get_char(value, pos)))
        pos++;

    start = pos;
    pos += http_header_quoted_string_len(value, pos);
    if (pos > start)
        warn_text = octstr_copy(value, start, pos - start);

    if (warn_agent == NULL && warn_text == NULL) {

        wsp_pack_short_integer(packed, warn_code);
    } else {

        Octstr *encoding = octstr_create("");

        if (warn_agent == NULL)
            warn_agent = octstr_create("");
        if (warn_text == NULL)
            warn_text = octstr_create("");

        wsp_pack_short_integer(encoding, warn_code);
        wsp_pack_text(encoding, warn_agent);
        wsp_pack_text(encoding, warn_text);
        wsp_pack_value(packed, encoding);
        octstr_destroy(encoding);
    }

    octstr_destroy(warn_agent);
    octstr_destroy(warn_text);
    return 0;

error:
    warning(0, "WSP: Cannot parse 'Warning: %s'.",
            octstr_get_cstr(value));
    octstr_destroy(warn_agent);
    octstr_destroy(warn_text);
    return -1;
}
