static void ncp_add_handle_path(struct ncp_server *server, __u8 vol_num,
				__le32 dir_base, int have_dir_base,
				const char *path)
{
	ncp_add_byte(server, vol_num);
	ncp_add_dword(server, dir_base);
	if (have_dir_base != 0) {
		ncp_add_byte(server, 1);
	} else {
		ncp_add_byte(server, 0xff);
	}
	if (path != NULL) {
		ncp_add_byte(server, 1);
		ncp_add_pstring(server, path);
	} else {
		ncp_add_byte(server, 0);
	}
}
