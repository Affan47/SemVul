keys_expire_values(struct keyinfo *ki, time_t now)
{
	struct keydata *kd;
	int i;
	int expired = 0;
	time_t next_expire = TIME_T_MAX;
	const char *reason = NULL;
	char buf[80];

	kd = get_keydata(ki->kuid);
	if (NULL == kd) {
		reason = "cannot retrieve associated keydata";
		goto discard_key;
	}

	if (kd->values != ki->values) {
		str_bprintf(buf, sizeof buf, "expected %u value%s, has %u in keydata",
			ki->values, 1 == ki->values ? "" : "s", kd->values);
		reason = buf;
		goto discard_key;
	}

	for (i = 0; i < kd->values; i++) {
		uint64 dbkey = kd->dbkeys[i];
		time_t expire = kd->expire[i];

		if (
			delta_time(now, expire) >= 0 &&
			values_has_expired(dbkey, now, &expire)
		) {
			expired++;


			if (kd->expire[i] != expire) {
				g_warning("DHT KEYS mismatching expire time for value #%d in %s"
					" (held %u, should have been %u)",
					i, kuid_to_hex_string(ki->kuid),
					(uint) kd->expire[i], (uint) expire);
			}
		} else {
			next_expire = MIN(expire, next_expire);
		}
	}

	if (GNET_PROPERTY(dht_storage_debug) > 3)
		g_debug("DHT STORE key %s has %d expired value%s out of %d",
			kuid_to_hex_string(ki->kuid), expired, 1 == expired ? "" : "s",
			ki->values);

	if (next_expire != TIME_T_MAX)
		ki->next_expire = next_expire;


	values_reclaim_expired();
	keyinfo_check(ki);
	return TRUE;

discard_key:


	g_warning("DHT KEYS discarding corrupted key %s (%u value%s): %s",
		kuid_to_hex_string(ki->kuid), ki->values, 1 == ki->values ? "" : "s",
		reason);

	keys_reclaim(ki, TRUE);
	return FALSE;
}
