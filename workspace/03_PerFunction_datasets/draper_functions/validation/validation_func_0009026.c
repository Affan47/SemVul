syncprov_operational(
	Operation *op,
	SlapReply *rs )
{
	slap_overinst		*on = (slap_overinst *)op->o_bd->bd_info;
	syncprov_info_t		*si = (syncprov_info_t *)on->on_bi.bi_private;


	if ( op->o_sync != SLAP_CONTROL_NONE )
		return SLAP_CB_CONTINUE;

	if ( rs->sr_entry &&
		dn_match( &rs->sr_entry->e_nname, &si->si_contextdn )) {

		if ( SLAP_OPATTRS( rs->sr_attr_flags ) ||
			ad_inlist( slap_schema.si_ad_contextCSN, rs->sr_attrs )) {
			Attribute *a, **ap = NULL;

			for ( a=rs->sr_entry->e_attrs; a; a=a->a_next ) {
				if ( a->a_desc == slap_schema.si_ad_contextCSN )
					break;
			}

			ldap_pvt_thread_rdwr_rlock( &si->si_csn_rwlock );
			if ( si->si_ctxcsn ) {
				if ( !a ) {
					for ( ap = &rs->sr_operational_attrs; *ap;
						ap=&(*ap)->a_next );

					a = attr_alloc( slap_schema.si_ad_contextCSN );
					*ap = a;
				}

				if ( !ap ) {
					if ( rs_entry2modifiable( op, rs, on )) {
						a = attr_find( rs->sr_entry->e_attrs,
							slap_schema.si_ad_contextCSN );
					}
					if ( a->a_nvals != a->a_vals ) {
						ber_bvarray_free( a->a_nvals );
					}
					a->a_nvals = NULL;
					ber_bvarray_free( a->a_vals );
					a->a_vals = NULL;
					a->a_numvals = 0;
				}
				attr_valadd( a, si->si_ctxcsn, si->si_ctxcsn, si->si_numcsns );
			}
			ldap_pvt_thread_rdwr_runlock( &si->si_csn_rwlock );
		}
	}
	return SLAP_CB_CONTINUE;
}
