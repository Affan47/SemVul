ldif_back_modify( Operation *op, SlapReply *rs )
{
	struct ldif_info *li = (struct ldif_info *) op->o_bd->be_private;
	Modifications * modlst = op->orm_modlist;
	struct berval path;
	Entry *entry;
	char textbuf[SLAP_TEXT_BUFLEN];
	int rc;

	slap_mods_opattrs( op, &op->orm_modlist, 1 );

	ldap_pvt_thread_mutex_lock( &li->li_modop_mutex );

	rc = get_entry( op, &entry, &path, &rs->sr_text );
	if ( rc == LDAP_SUCCESS ) {
		rc = apply_modify_to_entry( entry, modlst, op, rs, textbuf );
		if ( rc == LDAP_SUCCESS ) {
			ldap_pvt_thread_rdwr_wlock( &li->li_rdwr );
			rc = ldif_write_entry( op, entry, &path, NULL, &rs->sr_text );
			ldap_pvt_thread_rdwr_wunlock( &li->li_rdwr );
		}

		entry_free( entry );
		SLAP_FREE( path.bv_val );
	}

	ldap_pvt_thread_mutex_unlock( &li->li_modop_mutex );

	rs->sr_err = rc;
	send_ldap_result( op, rs );
	slap_graduate_commit_csn( op );
	rs->sr_text = NULL;
	return rs->sr_err;
}
