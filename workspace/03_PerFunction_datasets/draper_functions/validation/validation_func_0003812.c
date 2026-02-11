cr_add(
    LDAPContentRule	*cr,
	int user,
	ContentRule **rscr,
    const char		**err
)
{
	ContentRule	*scr;
	int		code;
	int		op = 0;
	char	*oidm = NULL;

	if ( cr->cr_names != NULL ) {
		int i;

		for( i=0; cr->cr_names[i]; i++ ) {
			if( !slap_valid_descr( cr->cr_names[i] ) ) {
				return SLAP_SCHERR_BAD_DESCR;
			}
		}
	}

	if ( !OID_LEADCHAR( cr->cr_oid[0] )) {

		char *oid = oidm_find( cr->cr_oid );
		if ( !oid ) {
			*err = cr->cr_oid;
			return SLAP_SCHERR_OIDM;
		}
		if ( oid != cr->cr_oid ) {
			oidm = cr->cr_oid;
			cr->cr_oid = oid;
		}
	}

	scr = (ContentRule *) ch_calloc( 1, sizeof(ContentRule) );
	AC_MEMCPY( &scr->scr_crule, cr, sizeof(LDAPContentRule) );

	scr->scr_oidmacro = oidm;
	scr->scr_sclass = oc_find(cr->cr_oid);
	if ( !scr->scr_sclass ) {
		*err = cr->cr_oid;
		code = SLAP_SCHERR_CLASS_NOT_FOUND;
		goto fail;
	}


	if( scr->scr_sclass->soc_kind != LDAP_SCHEMA_STRUCTURAL )
	{
		*err = cr->cr_oid;
		code = SLAP_SCHERR_CR_BAD_STRUCT;
		goto fail;
	}

	if( scr->scr_sclass->soc_flags & SLAP_OC_OPERATIONAL ) op++;

	code = cr_add_auxiliaries( scr, &op, err );
	if ( code != 0 ) goto fail;

	code = cr_create_required( scr, &op, err );
	if ( code != 0 ) goto fail;

	code = cr_create_allowed( scr, &op, err );
	if ( code != 0 ) goto fail;

	code = cr_create_precluded( scr, &op, err );
	if ( code != 0 ) goto fail;

	if( user && op ) {
		code = SLAP_SCHERR_CR_BAD_AUX;
		goto fail;
	}

	code = cr_insert(scr,err);
	if ( code == 0 && rscr )
		*rscr = scr;
	return code;
fail:
	ch_free( scr );
	return code;
}
