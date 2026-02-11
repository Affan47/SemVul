hsep_get_connection_table(const struct gnutella_node *n,
    hsep_triple *buffer, unsigned int maxtriples)
{
	g_assert(n);
	g_assert(n->hsep);
	g_assert(buffer);

	maxtriples = MIN(maxtriples, G_N_ELEMENTS(n->hsep->table));
	memcpy(buffer, n->hsep->table, maxtriples * sizeof buffer[0]);

	return maxtriples;
}
