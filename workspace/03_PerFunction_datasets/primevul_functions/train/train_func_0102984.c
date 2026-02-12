static void mark_key_instantiated(struct key *key, int reject_error)
{


	smp_store_release(&key->state,
			  (reject_error < 0) ? reject_error : KEY_IS_POSITIVE);
}
