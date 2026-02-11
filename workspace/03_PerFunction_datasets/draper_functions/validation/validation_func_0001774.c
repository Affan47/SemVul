group_destroy(struct cdok_puzzle *puz, int grp,
			  const uint8_t *solution)
{
	struct cdok_group *g = &puz->groups[grp];
	int i;

	for (i = 0; i < g->size; i++) {
		const cdok_pos_t c = g->members[i];

		puz->values[c] = solution[c];
		puz->group_map[c] = CDOK_GROUP_NONE;
	}

	g->size = 0;
}
