slapi_attr_value_cmp( const Slapi_Attr *a, const struct berval *v1, const struct berval *v2 )
{
	MatchingRule *mr;
	int ret;
	int rc;
	const char *text;

	mr = a->a_desc->ad_type->sat_equality;
	rc = value_match( &ret, a->a_desc, mr,
			SLAP_MR_VALUE_OF_ASSERTION_SYNTAX,
		(struct berval *)v1, (void *)v2, &text );
	if ( rc != LDAP_SUCCESS )
		return -1;

	return ( ret == 0 ) ? 0 : -1;
}
