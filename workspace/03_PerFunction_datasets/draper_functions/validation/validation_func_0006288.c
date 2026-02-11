prg_cache_add(long inode, char *name)
{
	unsigned hi = PRG_HASHIT(inode);
	struct prg_node **pnp, *pn;

	prg_cache_loaded = 2;
	for (pnp = prg_hash + hi; (pn = *pnp) != NULL; pnp = &pn->next) {
		if (pn->inode == inode) {


			return;
		}
	}
	*pnp = xzalloc(sizeof(struct prg_node));
	pn = *pnp;
	pn->inode = inode;
	safe_strncpy(pn->name, name, PROGNAME_WIDTH);
}
