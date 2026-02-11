mark_dirty(Xdf_t *This, off_t begin, off_t end)
{
	int ptr;

	adjust_bounds(This, &begin, &end);

	ptr = begin;
	for(ptr=REC.begin; ptr < end ; ptr = REC.end) {
		REC.valid = 1;
		if(!REC.phantom)
			REC.dirty = 1;
	}
}
