accesslog_unbind( Operation *op, SlapReply *rs )
{
	slap_overinst *on = (slap_overinst *)op->o_bd->bd_info;
	if ( op->o_conn->c_authz_backend == on->on_info->oi_origdb ) {
		log_info *li = on->on_bi.bi_private;
		Operation op2 = {0};
		void *cids[SLAP_MAX_CIDS];
		SlapReply rs2 = {REP_RESULT};
		Entry *e;

		if ( !( li->li_ops & LOG_OP_UNBIND )) {
			log_base *lb;
			int i = 0;

			for ( lb = li->li_bases; lb; lb=lb->lb_next )
				if (( lb->lb_ops & LOG_OP_UNBIND ) && dnIsSuffix( &op->o_ndn, &lb->lb_base )) {
					i = 1;
					break;
				}
			if ( !i )
				return SLAP_CB_CONTINUE;
		}

		e = accesslog_entry( op, rs, LOG_EN_UNBIND, &op2 );
		op2.o_hdr = op->o_hdr;
		op2.o_tag = LDAP_REQ_ADD;
		op2.o_bd = li->li_db;
		op2.o_dn = li->li_db->be_rootdn;
		op2.o_ndn = li->li_db->be_rootndn;
		op2.o_req_dn = e->e_name;
		op2.o_req_ndn = e->e_nname;
		op2.ora_e = e;
		op2.o_callback = &nullsc;
		op2.o_controls = cids;
		memset(cids, 0, sizeof( cids ));

		op2.o_bd->be_add( &op2, &rs2 );
		if ( e == op2.ora_e )
			entry_free( e );
	}
	return SLAP_CB_CONTINUE;
}
