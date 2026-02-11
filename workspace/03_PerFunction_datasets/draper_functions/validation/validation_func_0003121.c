pmemalloc_reserve(void *pmp, size_t size)
{
	size_t nsize = roundup(size + PMEM_CHUNK_SIZE, PMEM_CHUNK_SIZE);
	struct clump *clp;

	DEBUG("pmp=0x%lx, size=0x%lx -> 0x%lx", pmp, size, nsize);

	clp = PMEM(pmp, (struct clump *)PMEM_CLUMP_OFFSET);

	if (clp->size == 0)
		FATAL("no clumps found");


	while (clp->size) {
		size_t sz = clp->size & ~PMEM_STATE_MASK;
		int state = clp->size & PMEM_STATE_MASK;

		DEBUG("[0x%lx] clump size 0x%lx state %d",
				OFF(pmp, clp), sz, state);

		if (state == PMEM_STATE_FREE && nsize <= sz) {
			void *ptr = (void *)
				(uintptr_t)clp + PMEM_CHUNK_SIZE -
				(uintptr_t)pmp;
			size_t leftover = sz - nsize;

			DEBUG("fit found ptr 0x%lx, leftover 0x%lx bytes",
					ptr, leftover);
			if (leftover >= PMEM_CHUNK_SIZE * 2) {
				struct clump *newclp;
				int i;

				newclp = (struct clump *)
					((uintptr_t)clp + nsize);

				DEBUG("splitting: [0x%lx] new clump",
						OFF(pmp, newclp));


				memset(newclp, '\0', sizeof(*newclp));
				newclp->size = leftover | PMEM_STATE_FREE;
				pmem_persist(newclp, sizeof(*newclp), 0);
				for (i = 0; i < PMEM_NUM_ON; i++) {
					clp->on[i].off = 0;
					clp->on[i].ptr_ = 0;
				}
				pmem_persist(clp, sizeof(*clp), 0);
				clp->size = nsize | PMEM_STATE_RESERVED;
				pmem_persist(clp, sizeof(*clp), 0);
			} else {
				int i;

				DEBUG("no split required");

				for (i = 0; i < PMEM_NUM_ON; i++) {
					clp->on[i].off = 0;
					clp->on[i].ptr_ = 0;
				}
				pmem_persist(clp, sizeof(*clp), 0);
				clp->size = sz | PMEM_STATE_RESERVED;
				pmem_persist(clp, sizeof(*clp), 0);
			}

			return ptr;
		}

		clp = (struct clump *)((uintptr_t)clp + sz);
		DEBUG("[0x%lx] next clump", OFF(pmp, clp));
	}

	DEBUG("no free memory of size %lu available", nsize);
	errno = ENOMEM;
	return NULL;
}
