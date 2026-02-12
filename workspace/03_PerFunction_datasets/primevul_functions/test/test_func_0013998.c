privateKeyValidate(
	Syntax		*syntax,
	struct berval	*val )
{
	BerElementBuffer berbuf;
	BerElement *ber = (BerElement *)&berbuf;
	ber_tag_t tag;
	ber_len_t len;
	ber_int_t version;

	ber_init2( ber, val, LBER_USE_DER );
	tag = ber_skip_tag( ber, &len );
	if ( tag != LBER_SEQUENCE ) return LDAP_INVALID_SYNTAX;
	tag = ber_peek_tag( ber, &len );
	if ( tag != LBER_INTEGER ) {

		if ( tag == LBER_SEQUENCE ) {
			ber_skip_data( ber, len );
			tag = ber_skip_tag( ber, &len );
			if ( tag != LBER_OCTETSTRING ) return LDAP_INVALID_SYNTAX;
			ber_skip_data( ber, len );
		} else
			return LDAP_INVALID_SYNTAX;
	} else {
		tag = ber_get_int( ber, &version );
		tag = ber_skip_tag( ber, &len );
		if ( tag != LBER_SEQUENCE ) return LDAP_INVALID_SYNTAX;
		ber_skip_data( ber, len );
		tag = ber_skip_tag( ber, &len );
		if ( tag != LBER_OCTETSTRING ) return LDAP_INVALID_SYNTAX;
		ber_skip_data( ber, len );
		tag = ber_skip_tag( ber, &len );
		if ( tag == LBER_SET ) {
			ber_skip_data( ber, len );
			tag = ber_skip_tag( ber, &len );
		}
	}


	if ( len || tag != LBER_DEFAULT ) return LDAP_INVALID_SYNTAX;
	return LDAP_SUCCESS;
}
