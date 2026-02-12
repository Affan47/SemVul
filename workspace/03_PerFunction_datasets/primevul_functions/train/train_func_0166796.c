int __key_link(struct key *keyring, struct key *key)
{
	struct keyring_list *klist, *nklist;
	unsigned max;
	size_t size;
	int loop, ret;

	ret = -EKEYREVOKED;
	if (test_bit(KEY_FLAG_REVOKED, &keyring->flags))
		goto error;

	ret = -ENOTDIR;
	if (keyring->type != &key_type_keyring)
		goto error;


	down_write(&keyring_serialise_link_sem);


	if (key->type == &key_type_keyring) {
		ret = keyring_detect_cycle(keyring, key);
		if (ret < 0)
			goto error2;
	}


	klist = keyring->payload.subscriptions;

	if (klist && klist->nkeys > 0) {
		struct key_type *type = key->type;

		for (loop = klist->nkeys - 1; loop >= 0; loop--) {
			if (klist->keys[loop]->type == type &&
			    strcmp(klist->keys[loop]->description,
				   key->description) == 0
			    ) {

				size = sizeof(struct key *) * klist->maxkeys;
				size += sizeof(*klist);
				BUG_ON(size > PAGE_SIZE);

				ret = -ENOMEM;
				nklist = kmemdup(klist, size, GFP_KERNEL);
				if (!nklist)
					goto error2;


				atomic_inc(&key->usage);
				nklist->keys[loop] = key;

				rcu_assign_pointer(
					keyring->payload.subscriptions,
					nklist);


				klist->delkey = loop;
				call_rcu(&klist->rcu,
					 keyring_unlink_rcu_disposal);

				goto done;
			}
		}
	}


	ret = key_payload_reserve(keyring,
				  keyring->datalen + KEYQUOTA_LINK_BYTES);
	if (ret < 0)
		goto error2;

	klist = keyring->payload.subscriptions;

	if (klist && klist->nkeys < klist->maxkeys) {

		atomic_inc(&key->usage);

		klist->keys[klist->nkeys] = key;
		smp_wmb();
		klist->nkeys++;
		smp_wmb();
	}
	else {

		max = 4;
		if (klist)
			max += klist->maxkeys;

		ret = -ENFILE;
		if (max > 65535)
			goto error3;
		size = sizeof(*klist) + sizeof(struct key *) * max;
		if (size > PAGE_SIZE)
			goto error3;

		ret = -ENOMEM;
		nklist = kmalloc(size, GFP_KERNEL);
		if (!nklist)
			goto error3;
		nklist->maxkeys = max;
		nklist->nkeys = 0;

		if (klist) {
			nklist->nkeys = klist->nkeys;
			memcpy(nklist->keys,
			       klist->keys,
			       sizeof(struct key *) * klist->nkeys);
		}


		atomic_inc(&key->usage);
		nklist->keys[nklist->nkeys++] = key;

		rcu_assign_pointer(keyring->payload.subscriptions, nklist);


		if (klist)
			call_rcu(&klist->rcu, keyring_link_rcu_disposal);
	}

done:
	ret = 0;
error2:
	up_write(&keyring_serialise_link_sem);
error:
	return ret;

error3:

	key_payload_reserve(keyring,
			    keyring->datalen - KEYQUOTA_LINK_BYTES);
	goto error2;

}
