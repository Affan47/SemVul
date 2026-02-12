bitStringValidate(
	Syntax *syntax,
	struct berval *in )
{
	ber_len_t i;


	if( in->bv_len < 3 ) {
		return LDAP_INVALID_SYNTAX;
	}


	if( in->bv_val[0] != '\'' ||
		in->bv_val[in->bv_len - 2] != '\'' ||
		in->bv_val[in->bv_len - 1] != 'B' )
	{
		return LDAP_INVALID_SYNTAX;
	}

	for( i = in->bv_len - 3; i > 0; i-- ) {
		if( in->bv_val[i] != '0' && in->bv_val[i] != '1' ) {
			return LDAP_INVALID_SYNTAX;
		}
	}

	return LDAP_SUCCESS;
}
