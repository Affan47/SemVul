size_buffer(isc_mem_t *mctx, isc_buffer_t *b, unsigned size) {
	if (b->length < size) {
		void *mem = isc_mem_get(mctx, size);
		if (mem == NULL)
			return (ISC_R_NOMEMORY);
		if (b->base != NULL)
			isc_mem_put(mctx, b->base, b->length);
		b->base = mem;
		b->length = size;
	}
	isc_buffer_clear(b);
	return (ISC_R_SUCCESS);
}
