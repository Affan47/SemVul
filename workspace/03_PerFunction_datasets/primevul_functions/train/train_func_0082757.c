int hpack_dht_insert(struct hpack_dht *dht, struct ist name, struct ist value)
{
	unsigned int used;
	unsigned int head;
	unsigned int prev;
	unsigned int wrap;
	unsigned int tail;
	uint32_t headroom, tailroom;

	if (!hpack_dht_make_room(dht, name.len + value.len))
		return 0;


	used = dht->used;
	if (!used) {

		dht->front = dht->head = 0;
		dht->wrap  = dht->used = 1;
		dht->total = 0;
		head = 0;
		dht->dte[head].addr = dht->size - (name.len + value.len);
		goto copy;
	}


	prev = head = dht->head;
	wrap = dht->wrap;
	tail = hpack_dht_get_tail(dht);

	used++;
	head++;

	if (head >= wrap) {


		if ((sizeof(*dht) + (wrap + 1) * sizeof(dht->dte[0]) <= dht->dte[dht->front].addr))
			wrap++;
		else if (head >= used)
			head = 0;
		else {


			if (!hpack_dht_defrag(dht))
				return -1;

			wrap = dht->wrap + 1;
			head = dht->head + 1;
			prev = head - 1;
			tail = 0;
		}
	}
	else if (used >= wrap) {


		if (!hpack_dht_defrag(dht))
			return -1;

		wrap = dht->wrap + 1;
		head = dht->head + 1;
		prev = head - 1;
		tail = 0;
	}


	if (prev == dht->front) {

		headroom = dht->dte[dht->front].addr - (sizeof(*dht) + wrap * sizeof(dht->dte[0]));
		tailroom = dht->size - dht->dte[tail].addr - dht->dte[tail].nlen - dht->dte[tail].vlen;
	}
	else {

		headroom = 0;
		tailroom = dht->dte[prev].addr - dht->dte[tail].addr - dht->dte[tail].nlen - dht->dte[tail].vlen;
	}


	if (headroom >= name.len + value.len) {

		dht->dte[head].addr = dht->dte[dht->front].addr - (name.len + value.len);
		dht->front = head;
	}
	else if (tailroom >= name.len + value.len) {
		dht->dte[head].addr = dht->dte[tail].addr + dht->dte[tail].nlen + dht->dte[tail].vlen + tailroom - (name.len + value.len);
	}
	else {

		dht = hpack_dht_defrag(dht);
		wrap = dht->wrap + 1;
		head = dht->head + 1;
		dht->dte[head].addr = dht->dte[dht->front].addr - (name.len + value.len);
		dht->front = head;
	}

	dht->wrap = wrap;
	dht->head = head;
	dht->used = used;

 copy:
	dht->total         += name.len + value.len;
	dht->dte[head].nlen = name.len;
	dht->dte[head].vlen = value.len;

	memcpy((void *)dht + dht->dte[head].addr, name.ptr, name.len);
	memcpy((void *)dht + dht->dte[head].addr + name.len, value.ptr, value.len);
	return 0;
}
