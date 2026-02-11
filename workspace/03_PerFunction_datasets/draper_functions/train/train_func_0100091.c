nvkm_mm_head(struct nvkm_mm *mm, u8 heap, u8 type, u32 size_max, u32 size_min,
	     u32 align, struct nvkm_mm_node **pnode)
{
	struct nvkm_mm_node *prev, *this, *next;
	u32 mask = align - 1;
	u32 splitoff;
	u32 s, e;

	BUG_ON(type == NVKM_MM_TYPE_NONE || type == NVKM_MM_TYPE_HOLE);

	list_for_each_entry(this, &mm->free, fl_entry) {
		if (unlikely(heap != NVKM_MM_HEAP_ANY)) {
			if (this->heap != heap)
				continue;
		}
		e = this->offset + this->length;
		s = this->offset;

		prev = node(this, prev);
		if (prev && prev->type != type)
			s = roundup(s, mm->block_size);

		next = node(this, next);
		if (next && next->type != type)
			e = rounddown(e, mm->block_size);

		s  = (s + mask) & ~mask;
		e &= ~mask;
		if (s > e || e - s < size_min)
			continue;

		splitoff = s - this->offset;
		if (splitoff && !region_head(mm, this, splitoff))
			return -ENOMEM;

		this = region_head(mm, this, min(size_max, e - s));
		if (!this)
			return -ENOMEM;

		this->type = type;
		list_del(&this->fl_entry);
		*pnode = this;
		return 0;
	}

	return -ENOSPC;
}
