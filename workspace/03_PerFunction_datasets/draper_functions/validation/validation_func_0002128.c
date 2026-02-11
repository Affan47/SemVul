load_bounds(Xdf_t *This, off_t begin, off_t end)
{
	off_t lbegin, lend;
	int endp1, endp2;

	lbegin = begin;
	lend = end;

	adjust_bounds(This, &lbegin, &lend);

	if(begin != BEGIN(lbegin) * This->sector_size &&
	   end != BEGIN(lend) * This->sector_size &&
	   lend < END(END(lbegin)))

		return load_data(This, begin, end, 4);

	if(begin != BEGIN(lbegin) * This->sector_size) {
		endp1 = load_data(This, begin, begin, 4);
		if(endp1 < 0)
			return endp1;
	}

	if(end != BEGIN(lend) * This->sector_size) {
		endp2 = load_data(This, end, end, 4);
		if(endp2 < 0)
			return BEGIN(lend) * This->sector_size;
	}
	return lend * This->sector_size;
}
