text_array_get(struct text_array *t, int x, int y)
{
	if(x < 0 || y < 0 || x >= t->width || y >= t->height)
		return 0;
	return t->data[y * t->width + x];
}
