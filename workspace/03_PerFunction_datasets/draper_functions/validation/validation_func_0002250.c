dump_arp(void)
{
	ulong	arp_tbl;
	ulong	*hash_buckets;
	ulong	hash;
	long	hash_bytes;
	int	nhash_buckets = 0;
	int	key_len;
	int	i;
	int	header_printed = 0;
	int	hash_mask = 0;
	ulong	nht;

	if (!symbol_exists("arp_tbl"))
		error(FATAL, "arp_tbl does not exist in this kernel\n");

	arp_tbl = symbol_value("arp_tbl");


	if (VALID_MEMBER(neigh_table_nht_ptr)) {
		readmem(arp_tbl + OFFSET(neigh_table_nht_ptr),
			KVADDR, &nht, sizeof(nht),
			"neigh_table nht", FAULT_ON_ERROR);


		if (VALID_MEMBER(neigh_table_hash_mask)) {
			readmem(nht + OFFSET(neigh_table_hash_mask),
				KVADDR, &hash_mask, sizeof(hash_mask),
				"neigh_hash_table hash_mask", FAULT_ON_ERROR);

			nhash_buckets = hash_mask + 1;
		} else if (VALID_MEMBER(neigh_table_hash_shift)) {
			readmem(nht + OFFSET(neigh_table_hash_shift),
				KVADDR, &hash_mask, sizeof(hash_mask),
				"neigh_hash_table hash_shift", FAULT_ON_ERROR);

			nhash_buckets = 1U << hash_mask;
		}
	} else if (VALID_MEMBER(neigh_table_hash_mask)) {
		readmem(arp_tbl + OFFSET(neigh_table_hash_mask),
			KVADDR, &hash_mask, sizeof(hash_mask),
			"neigh_table hash_mask", FAULT_ON_ERROR);

		nhash_buckets = hash_mask + 1;
	} else
		nhash_buckets = (i = ARRAY_LENGTH(neigh_table_hash_buckets)) ?
			i : get_array_length("neigh_table.hash_buckets",
				NULL, sizeof(void *));

	if (nhash_buckets == 0) {
		option_not_supported('a');
		return;
	}

	hash_bytes = nhash_buckets * sizeof(*hash_buckets);

	hash_buckets = (ulong *)GETBUF(hash_bytes);

	readmem(arp_tbl + OFFSET(neigh_table_key_len),
		KVADDR, &key_len, sizeof(key_len),
		"neigh_table key_len", FAULT_ON_ERROR);

	if (VALID_MEMBER(neigh_table_nht_ptr)) {
		readmem(nht + OFFSET(neigh_table_hash_buckets),
			KVADDR, &hash, sizeof(hash),
			"neigh_hash_table hash_buckets ptr", FAULT_ON_ERROR);

		readmem(hash, KVADDR, hash_buckets, hash_bytes,
			"neigh_hash_table hash_buckets", FAULT_ON_ERROR);
	} else if (hash_mask) {
		readmem(arp_tbl + OFFSET(neigh_table_hash_buckets),
			KVADDR, &hash, sizeof(hash),
			"neigh_table hash_buckets pointer", FAULT_ON_ERROR);

		readmem(hash,
			KVADDR, hash_buckets, hash_bytes,
			"neigh_table hash_buckets", FAULT_ON_ERROR);
	} else
		readmem(arp_tbl + OFFSET(neigh_table_hash_buckets),
			KVADDR, hash_buckets, hash_bytes,
			"neigh_table hash_buckets", FAULT_ON_ERROR);

	for (i = 0; i < nhash_buckets; i++) {
		if (hash_buckets[i] != (ulong)NULL) {
			if (!header_printed) {
				fprintf(fp, "%s\n", ARP_HEADING);
				header_printed = 1;
			}
			print_neighbour_q(hash_buckets[i], key_len);
		}
	}

	fflush(fp);

	FREEBUF(hash_buckets);
}
