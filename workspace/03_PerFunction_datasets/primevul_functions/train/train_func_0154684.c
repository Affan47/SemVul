bool ikev1_decode_peer_id(struct msg_digest *md, bool initiator, bool aggrmode)
{
	struct state *const st = md->st;
	struct connection *c = st->st_connection;
	const struct payload_digest *const id_pld = md->chain[ISAKMP_NEXT_ID];
	const struct isakmp_id *const id = &id_pld->payload.id;


	if (st->hidden_variables.st_nat_traversal != LEMPTY &&
	    id->isaid_doi_specific_a == IPPROTO_UDP &&
	    (id->isaid_doi_specific_b == 0 ||
	     id->isaid_doi_specific_b == pluto_nat_port)) {
		DBG_log("protocol/port in Phase 1 ID Payload is %d/%d. accepted with port_floating NAT-T",
			id->isaid_doi_specific_a, id->isaid_doi_specific_b);
	} else if (!(id->isaid_doi_specific_a == 0 &&
		     id->isaid_doi_specific_b == 0) &&
		   !(id->isaid_doi_specific_a == IPPROTO_UDP &&
		     id->isaid_doi_specific_b == pluto_port))
	{
		loglog(RC_LOG_SERIOUS,
			"protocol/port in Phase 1 ID Payload MUST be 0/0 or %d/%d but are %d/%d (attempting to continue)",
			IPPROTO_UDP, pluto_port,
			id->isaid_doi_specific_a,
			id->isaid_doi_specific_b);


	}

	struct id peer;

	if (!extract_peer_id(id->isaid_idtype, &peer, &id_pld->pbs))
		return FALSE;

	if (c->spd.that.id.kind == ID_FROMCERT) {

		duplicate_id(&c->spd.that.id, &peer);
	}


	st->st_peeridentity_protocol = id->isaid_doi_specific_a;
	st->st_peeridentity_port = ntohs(id->isaid_doi_specific_b);

	{
		id_buf buf;

		libreswan_log("Peer ID is %s: '%s'",
			enum_show(&ike_idtype_names, id->isaid_idtype),
			str_id(&peer, &buf));
	}


	if (!v1_verify_certs(md)) {
		libreswan_log("X509: CERT payload does not match connection ID");
		if (initiator || aggrmode) {

			return false;
		}
	}


	ikev1_decode_cr(md);


	if (initiator) {
		if (!st->st_peer_alt_id &&
		    !same_id(&c->spd.that.id, &peer) &&
		    c->spd.that.id.kind != ID_FROMCERT) {
			id_buf expect;
			id_buf found;

			loglog(RC_LOG_SERIOUS,
			       "we require IKEv1 peer to have ID '%s', but peer declares '%s'",
			       str_id(&c->spd.that.id, &expect),
			       str_id(&peer, &found));
			return FALSE;
		} else if (c->spd.that.id.kind == ID_FROMCERT) {
			if (peer.kind != ID_DER_ASN1_DN) {
				loglog(RC_LOG_SERIOUS,
				       "peer ID is not a certificate type");
				return FALSE;
			}
			duplicate_id(&c->spd.that.id, &peer);
		}
	} else if (!aggrmode) {

		uint16_t auth = xauth_calcbaseauth(st->st_oakley.auth);
		lset_t auth_policy;

		switch (auth) {
		case OAKLEY_PRESHARED_KEY:
			auth_policy = POLICY_PSK;
			break;
		case OAKLEY_RSA_SIG:
			auth_policy = POLICY_RSASIG;
			break;

		case OAKLEY_DSS_SIG:
		case OAKLEY_RSA_ENC:
		case OAKLEY_RSA_REVISED_MODE:
		case OAKLEY_ECDSA_P256:
		case OAKLEY_ECDSA_P384:
		case OAKLEY_ECDSA_P521:
		default:
			DBG(DBG_CONTROL, DBG_log("ikev1 ike_decode_peer_id bad_case due to not supported policy"));
			return FALSE;
		}

		bool fromcert;
		struct connection *r =
			refine_host_connection(st, &peer,
				NULL,
				FALSE,
				auth_policy,
				AUTHBY_UNSET,
				&fromcert);

		if (r == NULL) {
			DBG(DBG_CONTROL, {
				id_buf buf;

				DBG_log("no more suitable connection for peer '%s'",
					str_id(&peer, &buf));
			});

			if (!md->st->st_peer_alt_id &&
			    !same_id(&c->spd.that.id, &peer) &&
			    c->spd.that.id.kind != ID_FROMCERT) {
					libreswan_log("Peer mismatch on first found connection and no better connection found");
					return FALSE;
			} else {
				DBG(DBG_CONTROL, DBG_log("Peer ID matches and no better connection found - continuing with existing connection"));
				r = c;
			}
		}

		if (DBGP(DBG_BASE)) {
			dn_buf buf;
			DBG_log("offered CA: '%s'",
				str_dn_or_null(r->spd.this.ca, "%none", &buf));
		}

		if (r != c) {


			char b1[CONN_INST_BUF];
			char b2[CONN_INST_BUF];


			libreswan_log("switched from \"%s\"%s to \"%s\"%s",
				c->name,
				fmt_conn_instance(c, b1),
				r->name,
				fmt_conn_instance(r, b2));

			if (r->kind == CK_TEMPLATE || r->kind == CK_GROUP) {

				r = rw_instantiate(r, &c->spd.that.host_addr,
						   NULL,
						   &peer);
			}

			update_state_connection(st, r);
			c = r;

			DBG(DBG_CONTROL, DBG_log("retrying ike_decode_peer_id() with new conn"));
			passert(!initiator && !aggrmode);
			return ikev1_decode_peer_id(md, FALSE, FALSE);
		} else if (c->spd.that.has_id_wildcards) {
			duplicate_id(&c->spd.that.id, &peer);
			c->spd.that.has_id_wildcards = FALSE;
		} else if (fromcert) {
			DBG(DBG_CONTROL, DBG_log("copying ID for fromcert"));
			duplicate_id(&c->spd.that.id, &peer);
		}
	}

	return TRUE;
}
