scc_get_default_name(krb5_context context, char **str)
{
    krb5_error_code ret;
    char *name;

    *str = NULL;

    ret = get_def_name(context, &name);
    if (ret)
	return _krb5_expand_default_cc_name(context, KRB5_SCACHE_NAME, str);

    ret = asprintf(str, "SCC:%s", name);
    free(name);
    if (ret < 0 || *str == NULL)
	return krb5_enomem(context);
    return 0;
}
