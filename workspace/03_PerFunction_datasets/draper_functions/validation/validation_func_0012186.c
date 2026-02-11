kcm_alloc(krb5_context context, const char *name, krb5_ccache *id)
{
    krb5_kcmcache *k;

    k = malloc(sizeof(*k));
    if (k == NULL) {
	krb5_set_error_message(context, KRB5_CC_NOMEM,
			       N_("malloc: out of memory", ""));
	return KRB5_CC_NOMEM;
    }

    if (name != NULL) {
	k->name = strdup(name);
	if (k->name == NULL) {
	    free(k);
	    krb5_set_error_message(context, KRB5_CC_NOMEM,
				   N_("malloc: out of memory", ""));
	    return KRB5_CC_NOMEM;
	}
    } else
	k->name = NULL;

    (*id)->data.data = k;
    (*id)->data.length = sizeof(*k);

    return 0;
}
