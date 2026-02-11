mdb_entry_get(
	Operation *op,
	struct berval *ndn,
	ObjectClass *oc,
	AttributeDescription *at,
	int rw,
	Entry **ent )
{
	struct mdb_info *mdb = (struct mdb_info *) op->o_bd->be_private;
	struct mdb_op_info *moi = NULL;
	MDB_txn *txn = NULL;
	Entry *e = NULL;
	int	rc;
	const char *at_name = at ? at->ad_cname.bv_val : "(null)";

	Debug( LDAP_DEBUG_ARGS,
		"=> mdb_entry_get: ndn: \"%s\"\n", ndn->bv_val, 0, 0 );
	Debug( LDAP_DEBUG_ARGS,
		"=> mdb_entry_get: oc: \"%s\", at: \"%s\"\n",
		oc ? oc->soc_cname.bv_val : "(null)", at_name, 0);

	rc = mdb_opinfo_get( op, mdb, rw == 0, &moi );
	if ( rc )
		return LDAP_OTHER;
	txn = moi->moi_txn;


	rc = mdb_dn2entry( op, txn, NULL, ndn, &e, 0 );
	switch( rc ) {
	case MDB_NOTFOUND:
	case 0:
		break;
	default:
		return (rc != LDAP_BUSY) ? LDAP_OTHER : LDAP_BUSY;
	}
	if (e == NULL) {
		Debug( LDAP_DEBUG_ACL,
			"=> mdb_entry_get: cannot find entry: \"%s\"\n",
				ndn->bv_val, 0, 0 );
		rc = LDAP_NO_SUCH_OBJECT;
		goto return_results;
	}

	Debug( LDAP_DEBUG_ACL,
		"=> mdb_entry_get: found entry: \"%s\"\n",
		ndn->bv_val, 0, 0 );

	if ( oc && !is_entry_objectclass( e, oc, 0 )) {
		Debug( LDAP_DEBUG_ACL,
			"<= mdb_entry_get: failed to find objectClass %s\n",
			oc->soc_cname.bv_val, 0, 0 );
		rc = LDAP_NO_SUCH_ATTRIBUTE;
		goto return_results;
	}


	if ( at && attr_find( e->e_attrs, at ) == NULL ) {
		Debug( LDAP_DEBUG_ACL,
			"<= mdb_entry_get: failed to find attribute %s\n",
			at->ad_cname.bv_val, 0, 0 );
		rc = LDAP_NO_SUCH_ATTRIBUTE;
		goto return_results;
	}

return_results:
	if( rc != LDAP_SUCCESS ) {

		if ( e )
			mdb_entry_return( op, e );

		if (moi->moi_ref == 1) {
			LDAP_SLIST_REMOVE( &op->o_extra, &moi->moi_oe, OpExtra, oe_next );
			mdb_txn_reset( txn );
			op->o_tmpfree( moi, op->o_tmpmemctx );
		}
	} else {
		*ent = e;
	}

	Debug( LDAP_DEBUG_TRACE,
		"mdb_entry_get: rc=%d\n",
		rc, 0, 0 );
	return(rc);
}
