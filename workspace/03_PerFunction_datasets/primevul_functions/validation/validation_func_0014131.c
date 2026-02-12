static void umd_cleanup(struct subprocess_info *info)
{
	struct umd_info *umd_info = info->data;


	if (info->retval)
		umd_cleanup_helper(umd_info);
}
