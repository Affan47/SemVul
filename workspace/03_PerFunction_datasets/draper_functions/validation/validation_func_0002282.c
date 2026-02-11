md_realloc(void *ptr, size_t size, const char *fname, int line)
{
	struct mem_t *mem = ptr ? container_of(ptr, typeof(*mem), data) : NULL;
	struct mem_t *mem2;

	if (mem) {
		if (mem->magic1 != MAGIC1) {
			printf("memory corruption:\nfree at %s:%i\n",
			       fname, line);
			abort();
		}

		if (mem->magic2 != *(uint64_t*)(mem->data + mem->size)) {
			printf("memory corruption:\nmalloc(%zu) at %s:%i\nfree at %s:%i\n",
			       mem->size, mem->fname, mem->line, fname, line);
			abort();
		}

		if (size == 0) {
			md_free(mem->data, fname, line);
			return NULL;
		}
	}

	mem2 = _md_malloc(size, fname, line);
	if (mem2 == NULL)
		return NULL;

	if (mem) {
		memcpy(mem2->data, mem->data,
		       (size < mem->size) ? size : mem->size);
		md_free(mem->data, fname, line);
	}

	return mem2->data;
}
