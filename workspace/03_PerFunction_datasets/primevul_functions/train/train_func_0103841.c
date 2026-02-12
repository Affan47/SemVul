value_free(
	struct value *vp
	)
{
	if (vp->ptr != NULL)
		free(vp->ptr);
	if (vp->sig != NULL)
		free(vp->sig);
	memset(vp, 0, sizeof(struct value));
}
