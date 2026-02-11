check_and_send_SASL_response(Slapi_PBlock *pb, ber_tag_t tag, BerElement *ber, Connection *conn)
{


	int rc= 0;
	if ( LDAP_RES_BIND == tag && conn->c_ldapversion >= LDAP_VERSION3 )
	{
		struct berval *bind_ret_saslcreds;
		slapi_pblock_get(pb, SLAPI_BIND_RET_SASLCREDS, &bind_ret_saslcreds);
		if ( bind_ret_saslcreds != NULL ) {
			rc = ber_printf( ber, "to",
			    LDAP_TAG_SASL_RES_CREDS,
			    bind_ret_saslcreds->bv_val ? bind_ret_saslcreds->bv_val : "",
			    bind_ret_saslcreds->bv_len );
		}
	}
	return rc;
}
