diva_alloc_dma_map_entry(struct _diva_dma_map_entry *pmap) {
	int i;
	for (i = 0; (pmap && pmap[i].local_ram_addr); i++) {
		if (!pmap[i].busy) {
			pmap[i].busy = 1;
			return (i);
		}
	}
	return (-1);
}
