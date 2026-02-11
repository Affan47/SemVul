label_cmp(struct aa_label *a, struct aa_label *b)
{
	AA_BUG(!b);

	if (a == b)
		return 0;

	return vec_cmp(a->vec, a->size, b->vec, b->size);
}
