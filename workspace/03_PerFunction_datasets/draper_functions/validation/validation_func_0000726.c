dgap_config_get_num_prts(struct board_t *bd)
{
	int count = 0;
	struct cnode *p;

	if (!bd)
		return 0;

	for (p = bd->bd_config; p; p = p->next) {
		switch (p->type) {
		case BNODE:


			if (p->u.board.type > EPCFE)
				count += p->u.board.nport;
			break;
		case CNODE:
			count += p->u.conc.nport;
			break;
		case MNODE:
			count += p->u.module.nport;
			break;
		}
	}
	return count;
}
