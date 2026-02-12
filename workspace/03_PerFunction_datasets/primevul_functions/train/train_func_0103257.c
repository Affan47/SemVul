static const char *nfs_readdir_copy_name(const char *name, unsigned int len)
{
	const char *ret = kmemdup_nul(name, len, GFP_KERNEL);


	if (ret != NULL)
		kmemleak_not_leak(ret);
	return ret;
}
