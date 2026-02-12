void process_v1_packet(struct msg_digest *md)
{
	const struct state_v1_microcode *smc;
	bool new_iv_set = FALSE;
	struct state *st = NULL;
	enum state_kind from_state = STATE_UNDEFINED;

#define SEND_NOTIFICATION(t) { \
		pstats(ikev1_sent_notifies_e, t); \
		if (st != NULL) \
			send_notification_from_state(st, from_state, t); \
		else \
			send_notification_from_md(md, t); }

	switch (md->hdr.isa_xchg) {
	case ISAKMP_XCHG_AGGR:
	case ISAKMP_XCHG_IDPROT:
		if (md->hdr.isa_msgid != v1_MAINMODE_MSGID) {
			plog_md(md, "Message ID was 0x%08" PRIx32 " but should be zero in phase 1",
				md->hdr.isa_msgid);
			SEND_NOTIFICATION(INVALID_MESSAGE_ID);
			return;
		}

		if (ike_spi_is_zero(&md->hdr.isa_ike_initiator_spi)) {
			plog_md(md, "Initiator Cookie must not be zero in phase 1 message");
			SEND_NOTIFICATION(INVALID_COOKIE);
			return;
		}

		if (ike_spi_is_zero(&md->hdr.isa_ike_responder_spi)) {


			if (md->hdr.isa_flags & ISAKMP_FLAGS_v1_ENCRYPTION) {
				plog_md(md, "initial phase 1 message is invalid: its Encrypted Flag is on");
				SEND_NOTIFICATION(INVALID_FLAGS);
				return;
			}


			st = find_state_ikev1_init(&md->hdr.isa_ike_initiator_spi,
						   md->hdr.isa_msgid);
			if (st != NULL) {
				so_serial_t old_state = push_cur_state(st);
				if (!ikev1_duplicate(st, md)) {


					log_state(RC_LOG, st, "discarding initial packet; already %s",
						  st->st_state->name);
				}
				pop_cur_state(old_state);
				return;
			}
			passert(st == NULL);

			from_state = (md->hdr.isa_xchg == ISAKMP_XCHG_IDPROT ?
				      STATE_MAIN_R0 : STATE_AGGR_R0);
		} else {


			st = find_state_ikev1(&md->hdr.isa_ike_spis,
					      md->hdr.isa_msgid);

			if (st == NULL) {


				st = find_state_ikev1_init(&md->hdr.isa_ike_initiator_spi,
							   md->hdr.isa_msgid);

				if (st == NULL) {
					plog_md(md, "phase 1 message is part of an unknown exchange");

					return;
				}
			}
			set_cur_state(st);
			from_state = st->st_state->kind;
		}
		break;

	case ISAKMP_XCHG_INFO:
		st = find_v1_info_state(&md->hdr.isa_ike_spis,
					v1_MAINMODE_MSGID);

		if (st == NULL) {


			st = find_state_ikev1_init(&md->hdr.isa_ike_initiator_spi,
						   v1_MAINMODE_MSGID);
		}

		if (st != NULL)
			set_cur_state(st);

		if (md->hdr.isa_flags & ISAKMP_FLAGS_v1_ENCRYPTION) {
			bool quiet = (st == NULL);

			if (st == NULL) {
				if (DBGP(DBG_BASE)) {
					DBG_log("Informational Exchange is for an unknown (expired?) SA with MSGID:0x%08" PRIx32,
						md->hdr.isa_msgid);
					DBG_dump_thing("- unknown SA's md->hdr.isa_ike_initiator_spi.bytes:",
						       md->hdr.isa_ike_initiator_spi);
					DBG_dump_thing("- unknown SA's md->hdr.isa_ike_responder_spi.bytes:",
						       md->hdr.isa_ike_responder_spi);
				}


				return;
			}

			if (!IS_ISAKMP_ENCRYPTED(st->st_state->kind)) {
				if (!quiet) {
					log_state(RC_LOG_SERIOUS, st,
						  "encrypted Informational Exchange message is invalid because no key is known");
				}

				return;
			}

			if (md->hdr.isa_msgid == v1_MAINMODE_MSGID) {
				if (!quiet) {
					log_state(RC_LOG_SERIOUS, st,
						  "Informational Exchange message is invalid because it has a Message ID of 0");
				}

				return;
			}

			if (!unique_msgid(st, md->hdr.isa_msgid)) {
				if (!quiet) {
					log_state(RC_LOG_SERIOUS, st,
						  "Informational Exchange message is invalid because it has a previously used Message ID (0x%08" PRIx32 " )",
						  md->hdr.isa_msgid);
				}

				return;
			}
			st->st_v1_msgid.reserved = FALSE;

			init_phase2_iv(st, &md->hdr.isa_msgid);
			new_iv_set = TRUE;

			from_state = STATE_INFO_PROTECTED;
		} else {
			if (st != NULL &&
			    IS_ISAKMP_AUTHENTICATED(st->st_state)) {
				log_state(RC_LOG_SERIOUS, st,
					  "Informational Exchange message must be encrypted");

				return;
			}
			from_state = STATE_INFO;
		}
		break;

	case ISAKMP_XCHG_QUICK:

		if (ike_spi_is_zero(&md->hdr.isa_ike_initiator_spi)) {
			dbg("Quick Mode message is invalid because it has an Initiator Cookie of 0");
			SEND_NOTIFICATION(INVALID_COOKIE);
			return;
		}

		if (ike_spi_is_zero(&md->hdr.isa_ike_responder_spi)) {
			dbg("Quick Mode message is invalid because it has a Responder Cookie of 0");
			SEND_NOTIFICATION(INVALID_COOKIE);
			return;
		}

		if (md->hdr.isa_msgid == v1_MAINMODE_MSGID) {
			dbg("Quick Mode message is invalid because it has a Message ID of 0");
			SEND_NOTIFICATION(INVALID_MESSAGE_ID);
			return;
		}

		st = find_state_ikev1(&md->hdr.isa_ike_spis,
				      md->hdr.isa_msgid);

		if (st == NULL) {


			st = find_state_ikev1(&md->hdr.isa_ike_spis,
					      v1_MAINMODE_MSGID);

			if (st == NULL) {
				dbg("Quick Mode message is for a non-existent (expired?) ISAKMP SA");

				return;
			}

			if (st->st_oakley.doing_xauth) {
				dbg("Cannot do Quick Mode until XAUTH done.");
				return;
			}


			if (st->st_state->kind == STATE_MODE_CFG_R2) {

				change_state(st, STATE_MAIN_R3);
			}

#ifdef SOFTREMOTE_CLIENT_WORKAROUND

			if (st->st_state->kind == STATE_MODE_CFG_R1) {
				log_state(RC_LOG, st,
					  "SoftRemote workaround: Cannot do Quick Mode until MODECFG done.");
				return;
			}
#endif

			set_cur_state(st);

			if (!IS_ISAKMP_SA_ESTABLISHED(st->st_state)) {
				log_state(RC_LOG_SERIOUS, st,
					  "Quick Mode message is unacceptable because it is for an incomplete ISAKMP SA");
				SEND_NOTIFICATION(PAYLOAD_MALFORMED );
				return;
			}

			if (!unique_msgid(st, md->hdr.isa_msgid)) {
				log_state(RC_LOG_SERIOUS, st,
					  "Quick Mode I1 message is unacceptable because it uses a previously used Message ID 0x%08" PRIx32 " (perhaps this is a duplicated packet)",
					  md->hdr.isa_msgid);
				SEND_NOTIFICATION(INVALID_MESSAGE_ID);
				return;
			}
			st->st_v1_msgid.reserved = FALSE;


			init_phase2_iv(st, &md->hdr.isa_msgid);
			new_iv_set = TRUE;

			from_state = STATE_QUICK_R0;
		} else {
			if (st->st_oakley.doing_xauth) {
				log_state(RC_LOG, st, "Cannot do Quick Mode until XAUTH done.");
				return;
			}
			set_cur_state(st);
			from_state = st->st_state->kind;
		}

		break;

	case ISAKMP_XCHG_MODE_CFG:
		if (ike_spi_is_zero(&md->hdr.isa_ike_initiator_spi)) {
			dbg("Mode Config message is invalid because it has an Initiator Cookie of 0");

			return;
		}

		if (ike_spi_is_zero(&md->hdr.isa_ike_responder_spi)) {
			dbg("Mode Config message is invalid because it has a Responder Cookie of 0");

			return;
		}

		if (md->hdr.isa_msgid == 0) {
			dbg("Mode Config message is invalid because it has a Message ID of 0");

			return;
		}

		st = find_v1_info_state(&md->hdr.isa_ike_spis, md->hdr.isa_msgid);

		if (st == NULL) {


			dbg("No appropriate Mode Config state yet. See if we have a Main Mode state");

			st = find_v1_info_state(&md->hdr.isa_ike_spis, 0);

			if (st == NULL) {
				dbg("Mode Config message is for a non-existent (expired?) ISAKMP SA");


				return;
			}

			set_cur_state(st);

			const struct end *this = &st->st_connection->spd.this;
			dbg(" processing received isakmp_xchg_type %s; this is a%s%s%s%s",
			    enum_show(&ikev1_exchange_names, md->hdr.isa_xchg),
			    this->xauth_server ? " xauthserver" : "",
			    this->xauth_client ? " xauthclient" : "",
			    this->modecfg_server ? " modecfgserver" : "",
			    this->modecfg_client ? " modecfgclient" : "");

			if (!IS_ISAKMP_SA_ESTABLISHED(st->st_state)) {
				dbg("Mode Config message is unacceptable because it is for an incomplete ISAKMP SA (state=%s)",
				    st->st_state->name);

				return;
			}
			dbg(" call  init_phase2_iv");
			init_phase2_iv(st, &md->hdr.isa_msgid);
			new_iv_set = TRUE;


			if (this->xauth_server &&
			    st->st_state->kind == STATE_XAUTH_R1 &&
			    st->quirks.xauth_ack_msgid) {
				from_state = STATE_XAUTH_R1;
				dbg(" set from_state to %s state is STATE_XAUTH_R1 and quirks.xauth_ack_msgid is TRUE",
				    st->st_state->name);
			} else if (this->xauth_client &&
				   IS_PHASE1(st->st_state->kind)) {
				from_state = STATE_XAUTH_I0;
				dbg(" set from_state to %s this is xauthclient and IS_PHASE1() is TRUE",
				    st->st_state->name);
			} else if (this->xauth_client &&
				   st->st_state->kind == STATE_XAUTH_I1) {


				from_state = STATE_XAUTH_I0;
				dbg(" set from_state to %s this is xauthclient and state == STATE_XAUTH_I1",
				    st->st_state->name);
			} else if (this->modecfg_server &&
				   IS_PHASE1(st->st_state->kind)) {
				from_state = STATE_MODE_CFG_R0;
				dbg(" set from_state to %s this is modecfgserver and IS_PHASE1() is TRUE",
				    st->st_state->name);
			} else if (this->modecfg_client &&
				   IS_PHASE1(st->st_state->kind)) {
				from_state = STATE_MODE_CFG_R1;
				dbg(" set from_state to %s this is modecfgclient and IS_PHASE1() is TRUE",
				    st->st_state->name);
			} else {
				dbg("received isakmp_xchg_type %s; this is a%s%s%s%s in state %s. Reply with UNSUPPORTED_EXCHANGE_TYPE",
				    enum_show(&ikev1_exchange_names, md->hdr.isa_xchg),
				    st->st_connection ->spd.this.xauth_server ? " xauthserver" : "",
				    st->st_connection->spd.this.xauth_client ? " xauthclient" : "",
				    st->st_connection->spd.this.modecfg_server ? " modecfgserver" : "",
				    st->st_connection->spd.this.modecfg_client  ? " modecfgclient" : "",
				    st->st_state->name);
				return;
			}
		} else {
			if (st->st_connection->spd.this.xauth_server &&
			    IS_PHASE1(st->st_state->kind)) {

				dbg("We were in phase 1, with no state, so we went to XAUTH_R0");
				change_state(st, STATE_XAUTH_R0);
			}


			set_cur_state(st);
			from_state = st->st_state->kind;
		}

		break;

	case ISAKMP_XCHG_NONE:
	case ISAKMP_XCHG_BASE:
	case ISAKMP_XCHG_AO:
	case ISAKMP_XCHG_NGRP:
	default:
		dbg("unsupported exchange type %s in message",
		    enum_show(&ikev1_exchange_names, md->hdr.isa_xchg));
		SEND_NOTIFICATION(UNSUPPORTED_EXCHANGE_TYPE);
		return;
	}


	if (md->hdr.isa_flags & ISAKMP_FLAGS_v1_COMMIT)
		dbg("IKE message has the Commit Flag set but Pluto doesn't implement this feature due to security concerns; ignoring flag");


	if (md->hdr.isa_np == ISAKMP_NEXT_IKE_FRAGMENTATION) {
		struct isakmp_ikefrag fraghdr;
		int last_frag_index = 0;
		pb_stream frag_pbs;

		if (st == NULL) {
			dbg("received IKE fragment, but have no state. Ignoring packet.");
			return;
		}

		if ((st->st_connection->policy & POLICY_IKE_FRAG_ALLOW) == 0) {
			dbg("discarding IKE fragment packet - fragmentation not allowed by local policy (ike_frag=no)");
			return;
		}

		if (!in_struct(&fraghdr, &isakmp_ikefrag_desc,
			       &md->message_pbs, &frag_pbs) ||
		    pbs_room(&frag_pbs) != fraghdr.isafrag_length ||
		    fraghdr.isafrag_np != ISAKMP_NEXT_NONE ||
		    fraghdr.isafrag_number == 0 ||
		    fraghdr.isafrag_number > 16) {
			SEND_NOTIFICATION(PAYLOAD_MALFORMED);
			return;
		}

		dbg("received IKE fragment id '%d', number '%u'%s",
		    fraghdr.isafrag_id,
		    fraghdr.isafrag_number,
		    (fraghdr.isafrag_flags == 1) ? "(last)" : "");

		struct v1_ike_rfrag *ike_frag = alloc_thing(struct v1_ike_rfrag, "ike_frag");
		ike_frag->md = md_addref(md, HERE);
		ike_frag->index = fraghdr.isafrag_number;
		ike_frag->last = (fraghdr.isafrag_flags & 1);
		ike_frag->size = pbs_left(&frag_pbs);
		ike_frag->data = frag_pbs.cur;


		struct v1_ike_rfrag **i = &st->st_v1_rfrags;
		for (;;) {
			if (ike_frag != NULL) {

				if (*i == NULL ||
				    (*i)->index > ike_frag->index) {
					ike_frag->next = *i;
					*i = ike_frag;
					ike_frag = NULL;
				} else if ((*i)->index == ike_frag->index) {

					struct v1_ike_rfrag *old = *i;

					ike_frag->next = old->next;
					*i = ike_frag;
					pexpect(old->md != NULL);
					release_any_md(&old->md);
					pfree(old);
					ike_frag = NULL;
				}
			}

			if (*i == NULL)
				break;

			if ((*i)->last)
				last_frag_index = (*i)->index;

			i = &(*i)->next;
		}


		if (last_frag_index != 0) {
			size_t size = 0;
			int prev_index = 0;

			for (struct v1_ike_rfrag *frag = st->st_v1_rfrags; frag; frag = frag->next) {
				size += frag->size;
				if (frag->index != ++prev_index) {
					break;
				} else if (frag->index == last_frag_index) {
					struct msg_digest *whole_md = alloc_md("msg_digest by ikev1 fragment handler");
					uint8_t *buffer = alloc_bytes(size,
								       "IKE fragments buffer");
					size_t offset = 0;

					whole_md->iface = frag->md->iface;
					whole_md->sender = frag->md->sender;


					frag = st->st_v1_rfrags;
					while (frag != NULL &&
					       frag->index <= last_frag_index)
					{
						passert(offset + frag->size <=
							size);
						memcpy(buffer + offset,
						       frag->data, frag->size);
						offset += frag->size;
						frag = frag->next;
					}

					init_pbs(&whole_md->packet_pbs, buffer, size,
						 "packet");

					process_packet(&whole_md);
					release_any_md(&whole_md);
					free_v1_message_queues(st);

					st->st_seen_fragments = TRUE;
					dbg(" updated IKE fragment state to respond using fragments without waiting for re-transmits");
					break;
				}
			}
		}

		return;
	}


	passert(STATE_IKEv1_FLOOR <= from_state && from_state < STATE_IKEv1_ROOF);
	const struct finite_state *fs = finite_states[from_state];
	passert(fs != NULL);
	smc = fs->v1_transitions;
	passert(smc != NULL);


	if (st != NULL) {
		oakley_auth_t baseauth =
			xauth_calcbaseauth(st->st_oakley.auth);

		while (!LHAS(smc->flags, baseauth)) {
			smc++;
			passert(smc->state == from_state);
		}
	}


	if (verbose_state_busy(st))
		return;


	if (st != NULL && ikev1_duplicate(st, md)) {
		return;
	}


	md->st = st;
	md->v1_from_state = from_state;
	md->smc = smc;
	md->new_iv_set = new_iv_set;


	if ((md->hdr.isa_flags & ISAKMP_FLAGS_v1_ENCRYPTION) &&
	    st != NULL &&
	    !st->hidden_variables.st_skeyid_calculated) {
		endpoint_buf b;
		dbg("received encrypted packet from %s but exponentiation still in progress",
		    str_endpoint(&md->sender, &b));


		if (st->st_suspended_md != NULL) {
			dbg("releasing suspended operation before completion: %p",
			    st->st_suspended_md);
			release_any_md(&st->st_suspended_md);
		}
		suspend_any_md(st, md);
		return;
	}

	process_packet_tail(md);

}
