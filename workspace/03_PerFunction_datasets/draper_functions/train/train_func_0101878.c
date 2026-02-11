trySimpleShrink(
	ANNpointArray		pa,
	ANNidxArray			pidx,
	int					n,
	int					dim,
	const ANNorthRect	&bnd_box,
	ANNorthRect			&inner_box)
{
	int i;

	annEnclRect(pa, pidx, n, dim, inner_box);

	ANNcoord max_length = 0;
	for (i = 0; i < dim; i++) {
		ANNcoord length = inner_box.hi[i] - inner_box.lo[i];
		if (length > max_length) {
			max_length = length;
		}
	}

	int shrink_ct = 0;
	for (i = 0; i < dim; i++) {

		ANNcoord gap_hi = bnd_box.hi[i] - inner_box.hi[i];

		if (gap_hi < max_length*BD_GAP_THRESH)
			inner_box.hi[i] = bnd_box.hi[i];
		else shrink_ct++;


		ANNcoord gap_lo = inner_box.lo[i] - bnd_box.lo[i];
		if (gap_lo < max_length*BD_GAP_THRESH)
			inner_box.lo[i] = bnd_box.lo[i];
		else shrink_ct++;
	}

	if (shrink_ct >= BD_CT_THRESH)
		 return SHRINK;
	else return SPLIT;
}
