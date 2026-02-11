__quota_error(struct super_block *sb, const char *func,
		   const char *fmt, ...)
{
	if (printk_ratelimit()) {
		va_list args;
		struct va_format vaf;

		va_start(args, fmt);

		vaf.fmt = fmt;
		vaf.va = &args;

		printk(KERN_ERR "Quota error (device %s): %s: %pV\n",
		       sb->s_id, func, &vaf);

		va_end(args);
	}
}
