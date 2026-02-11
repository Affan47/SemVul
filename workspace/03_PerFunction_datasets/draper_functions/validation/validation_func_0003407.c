fz_new_halftone(fz_context *ctx, int comps)
{
	fz_halftone *ht;
	int i;

	ht = fz_malloc(ctx, sizeof(fz_halftone) + (comps-1)*sizeof(fz_pixmap *));
	ht->refs = 1;
	ht->n = comps;
	for (i = 0; i < comps; i++)
		ht->comp[i] = NULL;

	return ht;
}
