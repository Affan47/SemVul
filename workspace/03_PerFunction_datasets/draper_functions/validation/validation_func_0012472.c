devm_kmemdup(struct device *dev, const void *src, size_t len, gfp_t gfp)
{
	void *p;

	p = devm_kmalloc(dev, len, gfp);
	if (p)
		memcpy(p, src, len);

	return p;
}
