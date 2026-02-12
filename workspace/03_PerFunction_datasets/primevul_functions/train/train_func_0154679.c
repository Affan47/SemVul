void complete_v1_state_transition(struct msg_digest *md, stf_status result)
{
	passert(md != NULL);


	pstats(ike_stf, PMIN(result, STF_FAIL));

	DBG(DBG_CONTROL,
	    DBG_log("complete v1 state transition with %s",
		    result > STF_FAIL ?
		    enum_name(&ikev1_notify_names, result - STF_FAIL) :
		    enum_name(&stf_status_names, result)));

	switch (result) {
	case STF_SUSPEND:
		set_cur_state(md->st);


		suspend_any_md(md->st, md);
		return;
	case STF_IGNORE:
		return;
	default:
		break;
	}


	enum state_kind from_state = md->v1_from_state;

	struct state *st = md->st;
	set_cur_state(st);

	passert(st != NULL);
	pexpect(!state_is_busy(st));

	if (result > STF_OK) {
		linux_audit_conn(md->st, IS_IKE_SA_ESTABLISHED(md->st) ? LAK_CHILD_FAIL : LAK_PARENT_FAIL);
	}

	switch (result) {
	case STF_OK:
	{

		const struct state_v1_microcode *smc = md->smc;

		DBG(DBG_CONTROL, DBG_log("doing_xauth:%s, t_xauth_client_done:%s",
			bool_str(st->st_oakley.doing_xauth),
			bool_str(st->hidden_variables.st_xauth_client_done)));


		if (md->fragvid) {
			dbg("peer supports fragmentation");
			st->st_seen_fragvid = TRUE;
		}

		if (md->dpd) {
			dbg("peer supports DPD");
			st->hidden_variables.st_peer_supports_dpd = TRUE;
			if (dpd_active_locally(st)) {
				dbg("DPD is configured locally");
			}
		}


		if (md->nortel) {
			dbg("peer requires Nortel Contivity workaround");
			st->st_seen_nortel_vid = TRUE;
		}

		if (!st->st_v1_msgid.reserved &&
		    IS_CHILD_SA(st) &&
		    st->st_v1_msgid.id != v1_MAINMODE_MSGID) {
			struct state *p1st = state_with_serialno(
				st->st_clonedfrom);

			if (p1st != NULL) {

				reserve_msgid(p1st, st->st_v1_msgid.id);
			}

			st->st_v1_msgid.reserved = TRUE;
		}

		dbg("IKEv1: transition from state %s to state %s",
		    finite_states[from_state]->name,
		    finite_states[smc->next_state]->name);

		change_state(st, smc->next_state);


		if (st->st_connection->spd.this.xauth_client &&
		    st->hidden_variables.st_xauth_client_done &&
		    !st->st_connection->spd.this.modecfg_client &&
		    st->st_state->kind == STATE_XAUTH_I1)
		{
			bool aggrmode = LHAS(st->st_connection->policy, POLICY_AGGRESSIVE_IX);

			libreswan_log("XAUTH completed; ModeCFG skipped as per configuration");
			change_state(st, aggrmode ? STATE_AGGR_I2 : STATE_MAIN_I4);
			st->st_v1_msgid.phase15 = v1_MAINMODE_MSGID;
		}


		if (!md->event_already_set) {


			DBG(DBG_CONTROL, DBG_log("event_already_set, deleting event"));


			delete_event(st);
			clear_retransmits(st);
		}


		free_v1_message_queues(st);


		free_chunk_content(&st->st_v1_rpacket);
		free_chunk_content(&st->st_v1_tpacket);


		if (nat_traversal_enabled && st->st_connection->ikev1_natt != NATT_NONE) {

			nat_traversal_change_port_lookup(md, st);
			v1_maybe_natify_initiator_endpoints(st, HERE);
		}


		remember_received_packet(st, md);
		st->st_v1_last_transition = md->smc;


		if (smc->flags & SMF_REPLY) {
			endpoint_buf b;
			endpoint_buf b2;
			pexpect_st_local_endpoint(st);
			dbg("sending reply packet to %s (from %s)",
			    str_endpoint(&st->st_remote_endpoint, &b),
			    str_endpoint(&st->st_interface->local_endpoint, &b2));

			close_output_pbs(&reply_stream);

			if (st->st_state->kind == STATE_MAIN_R2 &&
				impair.send_no_main_r2) {

				record_outbound_v1_ike_msg(st, &reply_stream,
							   finite_states[from_state]->name);
				libreswan_log("IMPAIR: Skipped sending STATE_MAIN_R2 response packet");
			} else {
				record_and_send_v1_ike_msg(st, &reply_stream,
							   finite_states[from_state]->name);
			}
		}


		if (!md->event_already_set) {
			DBG(DBG_CONTROL, DBG_log("!event_already_set at reschedule"));
			intmax_t delay_ms;
			enum event_type kind = smc->timeout_event;
			bool agreed_time = FALSE;
			struct connection *c = st->st_connection;


			if (c->spd.this.xauth_client &&
			    st->hidden_variables.st_xauth_client_done &&
			    !c->spd.this.modecfg_client &&
			    (st->st_state->kind == STATE_MAIN_I4 || st->st_state->kind == STATE_AGGR_I2))
			{
				DBG(DBG_CONTROL, DBG_log("fixup XAUTH without ModeCFG event from EVENT_RETRANSMIT to EVENT_SA_REPLACE"));
				kind = EVENT_SA_REPLACE;
			}

			switch (kind) {
			case EVENT_RETRANSMIT:
				start_retransmits(st);
				break;

			case EVENT_SA_REPLACE:
				if (IS_PHASE1(st->st_state->kind) ||
				    IS_PHASE15(st->st_state->kind)) {


					delay_ms = deltamillisecs(c->sa_ike_life_seconds);
					if ((c->policy & POLICY_DONT_REKEY) ||
					    delay_ms >= deltamillisecs(st->st_oakley.life_seconds))
					{
						agreed_time = TRUE;
						delay_ms = deltamillisecs(st->st_oakley.life_seconds);
					}
				} else {


					time_t delay = deltasecs(c->sa_ipsec_life_seconds);

#define clamp_delay(trans) { \
		if (st->trans.present && \
		    delay >= deltasecs(st->trans.attrs.life_seconds)) { \
			agreed_time = TRUE; \
			delay = deltasecs(st->trans.attrs.life_seconds); \
		} \
	}
					clamp_delay(st_ah);
					clamp_delay(st_esp);
					clamp_delay(st_ipcomp);
					delay_ms = delay * 1000;
#undef clamp_delay
				}


				if (agreed_time &&
				    (c->policy & POLICY_DONT_REKEY)) {
					kind = (smc->flags & SMF_INITIATOR) ?
					       EVENT_v1_SA_REPLACE_IF_USED :
					       EVENT_SA_EXPIRE;
				}
				if (kind != EVENT_SA_EXPIRE) {
					time_t marg =
						deltasecs(c->sa_rekey_margin);

					if (smc->flags & SMF_INITIATOR) {
						marg += marg *
							c->sa_rekey_fuzz /
							100.E0 *
							(rand() /
							 (RAND_MAX + 1.E0));
					} else {
						marg /= 2;
					}

					if (delay_ms > marg * 1000) {
						delay_ms -= marg * 1000;
						st->st_replace_margin = deltatime(marg);
					} else {
						kind = EVENT_SA_EXPIRE;
					}
				}

				event_schedule(kind, deltatime_ms(delay_ms), st);
				break;

			case EVENT_SO_DISCARD:
				event_schedule(EVENT_SO_DISCARD, c->r_timeout, st);
				break;

			default:
				bad_case(kind);
			}
		}


		{
			enum rc_type w;
			void (*log_details)(struct lswlog *buf, struct state *st);

			if (IS_IPSEC_SA_ESTABLISHED(st)) {
				pstat_sa_established(st);
				log_details = lswlog_child_sa_established;
				w = RC_SUCCESS;
			} else if (IS_ISAKMP_SA_ESTABLISHED(st->st_state)) {
				pstat_sa_established(st);
				log_details = lswlog_ike_sa_established;
				w = RC_SUCCESS;
			} else {
				log_details = NULL;
				w = RC_NEW_V1_STATE + st->st_state->kind;
			}

			passert(st->st_state->kind < STATE_IKEv1_ROOF);


			LSWLOG_RC(w, buf) {
				lswlogf(buf, "%s: %s", st->st_state->name,
					st->st_state->story);

				if (log_details != NULL) {
					log_details(buf, st);
				}
			}
		}


		if (IS_ISAKMP_SA_ESTABLISHED(st->st_state)) {
			if (dpd_init(st) != STF_OK) {
				loglog(RC_LOG_SERIOUS, "DPD initialization failed - continuing without DPD");
			}
		}


		if (st->st_connection->spd.this.xauth_server) {
			if (st->st_oakley.doing_xauth &&
			    IS_ISAKMP_SA_ESTABLISHED(st->st_state)) {
				DBG(DBG_CONTROLMORE|DBG_XAUTH,
				    DBG_log("XAUTH: Sending XAUTH Login/Password Request"));
				event_schedule(EVENT_v1_SEND_XAUTH,
					       deltatime_ms(EVENT_v1_SEND_XAUTH_DELAY_MS),
					       st);
				break;
			}
		}


		if (!IS_QUICK(st->st_state->kind) &&
		    st->st_connection->spd.this.xauth_client &&
		    !st->hidden_variables.st_xauth_client_done) {
			DBG(DBG_CONTROL,
			    DBG_log("XAUTH client is not yet authenticated"));
			break;
		}


		DBG(DBG_CONTROL,
		    DBG_log("modecfg pull: %s policy:%s %s",
			    (st->quirks.modecfg_pull_mode ?
			     "quirk-poll" : "noquirk"),
			    (st->st_connection->policy & POLICY_MODECFG_PULL) ?
			    "pull" : "push",
			    (st->st_connection->spd.this.modecfg_client ?
			     "modecfg-client" : "not-client")));

		if (st->st_connection->spd.this.modecfg_client &&
		    IS_ISAKMP_SA_ESTABLISHED(st->st_state) &&
		    (st->quirks.modecfg_pull_mode ||
		     st->st_connection->policy & POLICY_MODECFG_PULL) &&
		    !st->hidden_variables.st_modecfg_started) {
			DBG(DBG_CONTROL,
			    DBG_log("modecfg client is starting due to %s",
				    st->quirks.modecfg_pull_mode ? "quirk" :
				    "policy"));
			modecfg_send_request(st);
			break;
		}


		if (st->st_connection->spd.this.modecfg_server &&
		    IS_ISAKMP_SA_ESTABLISHED(st->st_state) &&
		    !st->hidden_variables.st_modecfg_vars_set &&
		    !(st->st_connection->policy & POLICY_MODECFG_PULL)) {
			change_state(st, STATE_MODE_CFG_R1);
			set_cur_state(st);
			libreswan_log("Sending MODE CONFIG set");


			modecfg_start_set(st);
			break;
		}


		if (!(smc->flags & SMF_INITIATOR) &&
		    IS_MODE_CFG_ESTABLISHED(st->st_state) &&
		    (st->st_seen_nortel_vid)) {
			libreswan_log("Nortel 'Contivity Mode' detected, starting Quick Mode");
			change_state(st, STATE_MAIN_R3);
			set_cur_state(st);
			quick_outI1(st->st_whack_sock, st, st->st_connection,
				    st->st_connection->policy, 1, SOS_NOBODY,
				    NULL
				    );
			break;
		}


		if (st->st_connection->spd.this.modecfg_client &&
		    IS_ISAKMP_SA_ESTABLISHED(st->st_state) &&
		    !st->hidden_variables.st_modecfg_vars_set) {
			DBG(DBG_CONTROL,
			    DBG_log("waiting for modecfg set from server"));
			break;
		}

		DBG(DBG_CONTROL,
		    DBG_log("phase 1 is done, looking for phase 2 to unpend"));

		if (smc->flags & SMF_RELEASE_PENDING_P2) {


			unpend(pexpect_ike_sa(st), NULL);
		}

		if (IS_ISAKMP_SA_ESTABLISHED(st->st_state) ||
		    IS_IPSEC_SA_ESTABLISHED(st))
			release_any_whack(st, HERE, "IKEv1 transitions finished");

		if (IS_QUICK(st->st_state->kind))
			break;

		break;
	}

	case STF_INTERNAL_ERROR:

		remember_received_packet(st, md);
		log_state(RC_INTERNALERR + md->v1_note, st,
			  "state transition function for %s had internal error",
			  st->st_state->name);
		release_pending_whacks(st, "internal error");
		break;

	case STF_FATAL:
		passert(st != NULL);

		remember_received_packet(st, md);
		log_state(RC_FATAL, st, "encountered fatal error in state %s",
			  st->st_state->name);
#ifdef HAVE_NM
		if (st->st_connection->remotepeertype == CISCO &&
		    st->st_connection->nmconfigured) {
			if (!do_command(st->st_connection,
					&st->st_connection->spd,
					"disconnectNM", st))
				DBG(DBG_CONTROL,
				    DBG_log("sending disconnect to NM failed, you may need to do it manually"));
		}
#endif
		release_pending_whacks(st, "fatal error");
		delete_state(st);
		md->st = st = NULL;
		break;

	default:
		passert(result > STF_FAIL);
		md->v1_note = result - STF_FAIL;

	case STF_FAIL:
	{


		const char *notify_name = (md->v1_note == NOTHING_WRONG ? "failed" :
					   enum_name(&ikev1_notify_names, md->v1_note));
		if (notify_name == NULL) {
			notify_name = "internal error";
		}


		if (md->v1_note != NOTHING_WRONG) {

			SEND_NOTIFICATION(md->v1_note);
		} else {

			log_state(WHACK_STREAM | (RC_NOTIFICATION + md->v1_note), st,
				  "state transition failed: %s", notify_name);
		}

		dbg("state transition function for %s failed: %s",
		    st->st_state->name, notify_name);

#ifdef HAVE_NM
		if (st->st_connection->remotepeertype == CISCO &&
		    st->st_connection->nmconfigured) {
			if (!do_command(st->st_connection,
					&st->st_connection->spd,
					"disconnectNM", st))
				DBG(DBG_CONTROL,
				    DBG_log("sending disconnect to NM failed, you may need to do it manually"));
		}
#endif
		if (IS_QUICK(st->st_state->kind)) {
			delete_state(st);

			md->st = NULL;
		}
		break;
	}
	}
}
