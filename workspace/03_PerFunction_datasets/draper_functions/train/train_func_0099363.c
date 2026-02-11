f_cmp_fkind(const void *a, const void *b)
{
	const feature_type *fa = &f_info[*(const int *)a];
	const feature_type *fb = &f_info[*(const int *)b];


	int c = feat_order(*(const int *)a) - feat_order(*(const int *)b);
	if (c) return c;


	return strcmp(fa->name, fb->name);
}
