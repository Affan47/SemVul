static ssize_t slab_attr_store(struct kobject *kobj,
				struct attribute *attr,
				const char *buf, size_t len)
{
	struct slab_attribute *attribute;
	struct kmem_cache *s;
	int err;

	attribute = to_slab_attr(attr);
	s = to_slab(kobj);

	if (!attribute->store)
		return -EIO;

	err = attribute->store(s, buf, len);
#ifdef CONFIG_MEMCG
	if (slab_state >= FULL && err >= 0 && is_root_cache(s)) {
		struct kmem_cache *c;

		mutex_lock(&slab_mutex);
		if (s->max_attr_size < len)
			s->max_attr_size = len;


		for_each_memcg_cache(c, s)
			attribute->store(c, buf, len);
		mutex_unlock(&slab_mutex);
	}
#endif
	return err;
}
