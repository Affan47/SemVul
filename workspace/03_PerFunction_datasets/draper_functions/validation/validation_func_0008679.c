resize(int sx, int sy)
{
	int min_width, min_height;
	getminbounds(&min_width, &min_height);
	if (size.w+sx <= min_width) sx = min_width - size.w;
	if (size.h+sy <= min_height) sy = min_height - size.h;

	ht_view::resize(sx, sy);

	ht_view *v = first;
	while (v) {
		reorder_view(v, sx, sy);
		v = v->next;
	}
}
