static ssize_t trace_store(struct kmem_cache *s, const char *buf,
							size_t length)
{


	if (s->refcount > 1)
		return -EINVAL;

	s->flags &= ~SLAB_TRACE;
	if (buf[0] == '1') {
		s->flags &= ~__CMPXCHG_DOUBLE;
		s->flags |= SLAB_TRACE;
	}
	return length;
}
