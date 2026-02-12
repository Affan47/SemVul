static int cache_update(struct server_data *srv, unsigned char *msg,
			unsigned int msg_len)
{
	int offset = protocol_offset(srv->protocol);
	int err, qlen, ttl = 0;
	uint16_t answers = 0, type = 0, class = 0;
	struct domain_hdr *hdr = (void *)(msg + offset);
	struct domain_question *q;
	struct cache_entry *entry;
	struct cache_data *data;
	char question[NS_MAXDNAME + 1];
	unsigned char response[NS_MAXDNAME + 1];
	unsigned char *ptr;
	unsigned int rsplen;
	bool new_entry = true;
	time_t current_time;

	if (cache_size >= MAX_CACHE_SIZE) {
		cache_cleanup();
		if (cache_size >= MAX_CACHE_SIZE)
			return 0;
	}

	current_time = time(NULL);


	if (next_refresh < current_time) {
		cache_refresh();
		next_refresh = current_time + 30;
	}

	if (offset < 0)
		return 0;

	debug("offset %d hdr %p msg %p rcode %d", offset, hdr, msg, hdr->rcode);


	if (hdr->rcode != ns_r_noerror)
		return 0;

	if (!cache)
		create_cache();

	rsplen = sizeof(response) - 1;
	question[sizeof(question) - 1] = '\0';

	err = parse_response(msg + offset, msg_len - offset,
				question, sizeof(question) - 1,
				&type, &class, &ttl,
				response, &rsplen, &answers);


	if ((err == -ENOMSG || err == -ENOBUFS) &&
			reply_query_type(msg + offset,
					msg_len - offset) == 28) {
		entry = g_hash_table_lookup(cache, question);
		if (entry && entry->ipv4 && !entry->ipv6) {
			int cache_offset = 0;

			data = g_try_new(struct cache_data, 1);
			if (!data)
				return -ENOMEM;
			data->inserted = entry->ipv4->inserted;
			data->type = type;
			data->answers = ntohs(hdr->ancount);
			data->timeout = entry->ipv4->timeout;
			if (srv->protocol == IPPROTO_UDP)
				cache_offset = 2;
			data->data_len = msg_len + cache_offset;
			data->data = ptr = g_malloc(data->data_len);
			ptr[0] = (data->data_len - 2) / 256;
			ptr[1] = (data->data_len - 2) - ptr[0] * 256;
			if (srv->protocol == IPPROTO_UDP)
				ptr += 2;
			data->valid_until = entry->ipv4->valid_until;
			data->cache_until = entry->ipv4->cache_until;
			memcpy(ptr, msg, msg_len);
			entry->ipv6 = data;


			entry->hits--;
			if (entry->hits < 0)
				entry->hits = 0;
			return 0;
		}
	}

	if (err < 0 || ttl == 0)
		return 0;

	qlen = strlen(question);


	entry = g_hash_table_lookup(cache, question);
	if (!entry) {
		entry = g_try_new(struct cache_entry, 1);
		if (!entry)
			return -ENOMEM;

		data = g_try_new(struct cache_data, 1);
		if (!data) {
			g_free(entry);
			return -ENOMEM;
		}

		entry->key = g_strdup(question);
		entry->ipv4 = entry->ipv6 = NULL;
		entry->want_refresh = false;
		entry->hits = 0;

		if (type == 1)
			entry->ipv4 = data;
		else
			entry->ipv6 = data;
	} else {
		if (type == 1 && entry->ipv4)
			return 0;

		if (type == 28 && entry->ipv6)
			return 0;

		data = g_try_new(struct cache_data, 1);
		if (!data)
			return -ENOMEM;

		if (type == 1)
			entry->ipv4 = data;
		else
			entry->ipv6 = data;


		entry->hits--;
		if (entry->hits < 0)
			entry->hits = 0;

		new_entry = false;
	}

	if (ttl < MIN_CACHE_TTL)
		ttl = MIN_CACHE_TTL;

	data->inserted = current_time;
	data->type = type;
	data->answers = answers;
	data->timeout = ttl;


	data->data_len = 2 + 12 + qlen + 1 + 2 + 2 + rsplen;
	data->data = ptr = g_malloc(data->data_len);
	data->valid_until = current_time + ttl;


	if (ttl > MAX_CACHE_TTL)
		ttl = MAX_CACHE_TTL;

	data->cache_until = round_down_ttl(current_time + ttl, ttl);

	if (!data->data) {
		g_free(entry->key);
		g_free(data);
		g_free(entry);
		return -ENOMEM;
	}


	if (srv->protocol == IPPROTO_UDP)
		memcpy(ptr + 2, msg, offset + 12);
	else
		memcpy(ptr, msg, offset + 12);

	ptr[0] = (data->data_len - 2) / 256;
	ptr[1] = (data->data_len - 2) - ptr[0] * 256;
	if (srv->protocol == IPPROTO_UDP)
		ptr += 2;

	memcpy(ptr + offset + 12, question, qlen + 1);

	q = (void *) (ptr + offset + 12 + qlen + 1);
	q->type = htons(type);
	q->class = htons(class);
	memcpy(ptr + offset + 12 + qlen + 1 + sizeof(struct domain_question),
		response, rsplen);

	if (new_entry) {
		g_hash_table_replace(cache, entry->key, entry);
		cache_size++;
	}

	debug("cache %d %squestion \"%s\" type %d ttl %d size %zd packet %u "
								"dns len %u",
		cache_size, new_entry ? "new " : "old ",
		question, type, ttl,
		sizeof(*entry) + sizeof(*data) + data->data_len + qlen,
		data->data_len,
		srv->protocol == IPPROTO_TCP ?
			(unsigned int)(data->data[0] * 256 + data->data[1]) :
			data->data_len);

	return 0;
}
