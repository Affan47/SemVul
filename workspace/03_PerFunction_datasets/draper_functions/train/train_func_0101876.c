matching_rule_use_init( void )
{
	MatchingRule	*mr;
	MatchingRuleUse	**mru_ptr = &LDAP_SLIST_FIRST(&mru_list);

	Debug( LDAP_DEBUG_TRACE, "matching_rule_use_init\n", 0, 0, 0 );

	LDAP_SLIST_FOREACH( mr, &mr_list, smr_next ) {
		AttributeType	*at;
		MatchingRuleUse	mru_storage = {{ 0 }},
				*mru = &mru_storage;

		char		**applies_oids = NULL;

		mr->smr_mru = NULL;


		if ( mr->smr_usage & SLAP_MR_HIDE ) {
			continue;
		}


		if (!( ( mr->smr_usage & SLAP_MR_EXT )
			|| mr->smr_compat_syntaxes ) )
		{
			continue;
		}


		mru->smru_mr = mr;
		mru->smru_obsolete = mr->smr_obsolete;
		mru->smru_applies_oids = NULL;
		LDAP_SLIST_NEXT(mru, smru_next) = NULL;
		mru->smru_oid = mr->smr_oid;
		mru->smru_names = mr->smr_names;
		mru->smru_desc = mr->smr_desc;

		Debug( LDAP_DEBUG_TRACE, "    %s (%s): ",
				mru->smru_oid,
				mru->smru_names ? mru->smru_names[ 0 ] : "", 0 );

		at = NULL;
		for ( at_start( &at ); at; at_next( &at ) ) {
			if( at->sat_flags & SLAP_AT_HIDE ) continue;

			if( mr_usable_with_at( mr, at )) {
				ldap_charray_add( &applies_oids, at->sat_cname.bv_val );
			}
		}


		if ( applies_oids != NULL ) {
			mru->smru_applies_oids = applies_oids;
			{
				char *str = ldap_matchingruleuse2str( &mru->smru_mruleuse );
				Debug( LDAP_DEBUG_TRACE, "matchingRuleUse: %s\n", str, 0, 0 );
				ldap_memfree( str );
			}

			mru = (MatchingRuleUse *)ber_memalloc( sizeof( MatchingRuleUse ) );

			mr->smr_mru = mru;

			*mru = mru_storage;

			*mru_ptr = mru;

			mru_ptr = &LDAP_SLIST_NEXT(mru,smru_next);
		}
	}

	return( 0 );
}
