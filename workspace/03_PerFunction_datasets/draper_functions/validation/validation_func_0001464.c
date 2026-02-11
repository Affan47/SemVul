found_left(void)
{
	struct found_struct *f = found_get();

	g_assert(!f->open);
	g_assert(f->pos <= sizeof f->data);
	return sizeof f->data - f->pos;
}
