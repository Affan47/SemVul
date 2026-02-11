krb5_parse_nametype(krb5_context context, const char *str, int32_t *nametype)
{
    size_t i;

    for(i = 0; nametypes[i].type; i++) {
	if (strcasecmp(nametypes[i].type, str) == 0) {
	    *nametype = nametypes[i].value;
	    return 0;
	}
    }
    krb5_set_error_message(context, KRB5_PARSE_MALFORMED,
			   N_("Failed to find name type %s", ""), str);
    return KRB5_PARSE_MALFORMED;
}
