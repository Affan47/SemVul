gbt_decode(struct pool *pool, json_t *res_val)
{
	const char *previousblockhash;
	const char *target;
	const char *coinbasetxn;
	const char *longpollid;
	unsigned char hash_swap[32];
	int expires;
	int version;
	int curtime;
	bool submitold;
	const char *bits;
	const char *workid;

	previousblockhash = json_string_value(json_object_get(res_val, "previousblockhash"));
	target = json_string_value(json_object_get(res_val, "target"));
	coinbasetxn = json_string_value(json_object_get(json_object_get(res_val, "coinbasetxn"), "data"));
	longpollid = json_string_value(json_object_get(res_val, "longpollid"));
	expires = json_integer_value(json_object_get(res_val, "expires"));
	version = json_integer_value(json_object_get(res_val, "version"));
	curtime = json_integer_value(json_object_get(res_val, "curtime"));
	submitold = json_is_true(json_object_get(res_val, "submitold"));
	bits = json_string_value(json_object_get(res_val, "bits"));
	workid = json_string_value(json_object_get(res_val, "workid"));

	if (!previousblockhash || !target || !coinbasetxn || !longpollid ||
	    !expires || !version || !curtime || !bits) {
		applog(LOG_ERR, "JSON failed to decode GBT");
		return false;
	}

	applog(LOG_DEBUG, "previousblockhash: %s", previousblockhash);
	applog(LOG_DEBUG, "target: %s", target);
	applog(LOG_DEBUG, "coinbasetxn: %s", coinbasetxn);
	applog(LOG_DEBUG, "longpollid: %s", longpollid);
	applog(LOG_DEBUG, "expires: %d", expires);
	applog(LOG_DEBUG, "version: %d", version);
	applog(LOG_DEBUG, "curtime: %d", curtime);
	applog(LOG_DEBUG, "submitold: %s", submitold ? "true" : "false");
	applog(LOG_DEBUG, "bits: %s", bits);
	if (workid)
		applog(LOG_DEBUG, "workid: %s", workid);

	cg_wlock(&pool->gbt_lock);
	free(pool->coinbasetxn);
	pool->coinbasetxn = strdup(coinbasetxn);
	free(pool->longpollid);
	pool->longpollid = strdup(longpollid);
	free(pool->gbt_workid);
	if (workid)
		pool->gbt_workid = strdup(workid);
	else
		pool->gbt_workid = NULL;

	hex2bin(hash_swap, previousblockhash, 32);
	swap256(pool->previousblockhash, hash_swap);

	hex2bin(hash_swap, target, 32);
	swab256(pool->gbt_target, hash_swap);

	pool->gbt_expires = expires;
	pool->gbt_version = htobe32(version);
	pool->curtime = htobe32(curtime);
	pool->submit_old = submitold;

	hex2bin((unsigned char *)&pool->gbt_bits, bits, 4);

	__build_gbt_txns(pool, res_val);
	cg_wunlock(&pool->gbt_lock);

	return true;
}
