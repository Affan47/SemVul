node_alloc(void)
{
	static const struct gnutella_node zero_node;
	struct gnutella_node *n;

	WALLOC(n);
	*n = zero_node;
	n->magic = NODE_MAGIC;
	return n;
}
