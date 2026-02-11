acc_get_first (krb5_context context,
	       krb5_ccache id,
	       krb5_cc_cursor *cursor)
{
    cc_credentials_iterator_t iter;
    krb5_acc *a = ACACHE(id);
    int32_t error;

    if (a->ccache == NULL) {
	krb5_set_error_message(context, KRB5_CC_NOTFOUND,
			       N_("No API credential found", ""));
	return KRB5_CC_NOTFOUND;
    }

    error = (*a->ccache->func->new_credentials_iterator)(a->ccache, &iter);
    if (error) {
	krb5_clear_error_message(context);
	return ENOENT;
    }
    *cursor = iter;
    return 0;
}
