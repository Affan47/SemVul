krb5_kt_next_entry(krb5_context context,
		   krb5_keytab id,
		   krb5_keytab_entry *entry,
		   krb5_kt_cursor *cursor)
{
    if(id->next_entry == NULL) {
	krb5_set_error_message(context, HEIM_ERR_OPNOTSUPP,
			       N_("next_entry is not supported in the %s "
				  " keytab", ""),
			       id->prefix);
	return HEIM_ERR_OPNOTSUPP;
    }
    return (*id->next_entry)(context, id, entry, cursor);
}
