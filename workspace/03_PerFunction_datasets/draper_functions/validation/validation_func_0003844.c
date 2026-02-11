markit(int64_t block, unsigned flag)
{
	int page, rem, word, bit;
	struct dmap *p1;
	int agno;
	int64_t num_blocks_left, nb;


	if (block > last_allocated && !(flag & BADBLOCK)) {
		last_allocated = block;
	}


	page = block / BPERDMAP;
	rem = block - page * BPERDMAP;
	word = rem >> L2DBWORD;
	bit = rem - (word << L2DBWORD);

	if (page > sz_block_map_array) {
		fprintf(stderr,
			"Internal error: %s(%d): Trying to mark block which doesn't exist.\n",
			__FILE__, __LINE__);
		return (-1);
	}


	if (block_map_array[page] == NULL) {
		num_blocks_left = control_page->dn_mapsize - (page * BPERDMAP);
		nb = MIN(BPERDMAP, num_blocks_left);
		block_map_array[page] = malloc(sizeof (struct dmap));
		if (block_map_array[page] == NULL) {
			message_user(MSG_OSO_INSUFF_MEMORY, NULL, 0, OSO_MSG);
			return (ENOMEM);
		}
		memset(block_map_array[page], 0, sizeof (struct dmap));
		ujfs_idmap_page(block_map_array[page], nb);
	}

	p1 = block_map_array[page];

	agno = block >> control_page->dn_agl2size;


	if (flag & ALLOC) {
		p1->pmap[word] |= (UZWORD >> bit);
		p1->wmap[word] |= (UZWORD >> bit);


		p1->nfree--;
		control_page->dn_nfree--;
		control_page->dn_agfree[agno]--;
	} else {
		p1->pmap[word] &= ~(UZWORD >> bit);
		p1->wmap[word] &= ~(UZWORD >> bit);


		p1->nfree++;
		control_page->dn_nfree++;
		control_page->dn_agfree[agno]++;
	}
	return (0);
}
