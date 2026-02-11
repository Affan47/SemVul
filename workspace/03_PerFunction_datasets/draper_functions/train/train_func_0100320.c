acc_get_next (krb5_context context,
	      krb5_ccache id,
	      krb5_cc_cursor *cursor,
	      krb5_creds *creds)
{
    cc_credentials_iterator_t iter = *cursor;
    cc_credentials_t cred;
    krb5_error_code ret;
    int32_t error;

    while (1) {
	error = (*iter->func->next)(iter, &cred);
	if (error)
	    return translate_cc_error(context, error);
	if (cred->data->version == cc_credentials_v5)
	    break;
	(*cred->func->release)(cred);
    }

    ret = make_cred_from_ccred(context,
			       cred->data->credentials.credentials_v5,
			       creds);
    (*cred->func->release)(cred);
    return ret;
}
