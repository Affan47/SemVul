print_download_id(gnet_fi_t handle, void *udata)
{
	struct gnutella_shell *sh = udata;
	gnet_fi_info_t *info;

	shell_check(sh);

	info = guc_fi_get_info(handle);
	g_return_if_fail(info);

	shell_write(sh, guid_to_string(info->guid));
	shell_write(sh, "\n");
}
