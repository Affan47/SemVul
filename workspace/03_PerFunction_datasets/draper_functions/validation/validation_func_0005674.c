dst__privstruct_free(dst_private_t *priv, isc_mem_t *mctx) {
	int i;

	if (priv == NULL)
		return;
	for (i = 0; i < priv->nelements; i++) {
		if (priv->elements[i].data == NULL)
			continue;
		memset(priv->elements[i].data, 0, MAXFIELDSIZE);
		isc_mem_put(mctx, priv->elements[i].data, MAXFIELDSIZE);
	}
	priv->nelements = 0;
}
