user_revoke(struct key *key)
{
	struct user_key_payload *upayload = key->payload.data[0];


	key_payload_reserve(key, 0);

	if (upayload) {
		rcu_assign_keypointer(key, NULL);
		kfree_rcu(upayload, rcu);
	}
}
