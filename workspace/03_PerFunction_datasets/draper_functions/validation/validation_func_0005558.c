terule_node_cmp(const void *a, const void *b, void *data __attribute__ ((unused)))
{
	const terule_node_t *an = a;
	const terule_node_t *bn = b;
	ssize_t retv = (const char *)an->src - (const char *)bn->src;
	if (retv > 0)
		return 1;
	else if (retv < 0)
		return -1;
	retv = (const char *)an->dflt - (const char *)bn->dflt;
	if (retv > 0)
		return 1;
	else if (retv < 0)
		return -1;
	retv = (const char *)an->rule - (const char *)bn->rule;
	if (retv > 0)
		return 1;
	else if (retv < 0)
		return -1;
	return 0;
}
