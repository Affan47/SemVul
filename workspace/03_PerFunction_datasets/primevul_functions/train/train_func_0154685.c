void init_ikev1(void)
{
	DBGF(DBG_CONTROL, "checking IKEv1 state table");


	for (enum state_kind kind = STATE_IKEv1_FLOOR; kind < STATE_IKEv1_ROOF; kind++) {

		const struct finite_state *fs = &v1_states[kind - STATE_IKEv1_FLOOR];
		passert(fs->kind == kind);
		passert(finite_states[kind] == NULL);
		finite_states[kind] = fs;
	}


	for (const struct state_v1_microcode *t = v1_state_microcode_table;
	     t->state < STATE_IKEv1_ROOF; t++) {

		passert(t->state >= STATE_IKEv1_FLOOR);
		passert(t->state < STATE_IKEv1_ROOF);
		struct finite_state *from = &v1_states[t->state - STATE_IKEv1_FLOOR];


		enum state_kind next_state = (t->next_state == STATE_UNDEFINED ?
					      t->state : t->next_state);
		passert(STATE_IKEv1_FLOOR <= next_state &&
			next_state < STATE_IKEv1_ROOF);
		const struct finite_state *to = finite_states[next_state];
		passert(to != NULL);

		if (DBGP(DBG_BASE)) {
			if (from->nr_transitions == 0) {
				LSWLOG_DEBUG(buf) {
					lswlogs(buf, "  ");
					lswlog_finite_state(buf, from);
					lswlogs(buf, ":");
				}
			}
			DBG_log("    -> %s %s (%s)", to->short_name,
				enum_short_name(&timer_event_names,
						t->timeout_event),
				t->message);
		}


		if (from->v1_transitions == NULL) {
			from->v1_transitions = t;
		} else {
			passert(t[-1].state == t->state);
		}
		from->nr_transitions++;

		if (t->message == NULL) {
			PEXPECT_LOG("transition %s -> %s missing .message",
				    from->short_name, to->short_name);
		}


		if ((t->flags & from->flags) != from->flags) {
			DBGF(DBG_BASE, "transition %s -> %s (%s) missing flags 0x%"PRIxLSET,
			     from->short_name, to->short_name,
			     t->message, from->flags);
		}
		from->flags |= t->flags & SMF_RETRANSMIT_ON_DUPLICATE;

		if (!(t->flags & SMF_FIRST_ENCRYPTED_INPUT) &&
		    (t->flags & SMF_INPUT_ENCRYPTED) &&
		    t->processor != unexpected) {


			if (!(t->req_payloads & LELEM(ISAKMP_NEXT_HASH))) {
				PEXPECT_LOG("transition %s -> %s (%s) missing HASH payload",
					    from->short_name, to->short_name,
					    t->message);
			}
			if (t->hash_type == V1_HASH_NONE) {
				PEXPECT_LOG("transition %s -> %s (%s) missing HASH protection",
					    from->short_name, to->short_name,
					    t->message);
			}
		}
	}
}
