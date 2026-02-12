static void memcg_propagate_slab_attrs(struct kmem_cache *s)
{
#ifdef CONFIG_MEMCG
	int i;
	char *buffer = NULL;
	struct kmem_cache *root_cache;

	if (is_root_cache(s))
		return;

	root_cache = s->memcg_params.root_cache;


	if (!root_cache->max_attr_size)
		return;

	for (i = 0; i < ARRAY_SIZE(slab_attrs); i++) {
		char mbuf[64];
		char *buf;
		struct slab_attribute *attr = to_slab_attr(slab_attrs[i]);
		ssize_t len;

		if (!attr || !attr->store || !attr->show)
			continue;


		if (buffer)
			buf = buffer;
		else if (root_cache->max_attr_size < ARRAY_SIZE(mbuf))
			buf = mbuf;
		else {
			buffer = (char *) get_zeroed_page(GFP_KERNEL);
			if (WARN_ON(!buffer))
				continue;
			buf = buffer;
		}

		len = attr->show(root_cache, buf);
		if (len > 0)
			attr->store(s, buf, len);
	}

	if (buffer)
		free_page((unsigned long)buffer);
#endif
}
