static int lookup_pi_state(u32 uval, struct futex_hash_bucket *hb,
			   union futex_key *key, struct futex_pi_state **ps)
{
	struct futex_q *match = futex_top_waiter(hb, key);


	if (match)
		return attach_to_pi_state(uval, match->pi_state, ps);


	return attach_to_pi_owner(uval, key, ps);
}
