ncp_DeleteNSEntry(struct ncp_server *server,
		  __u8 have_dir_base, __u8 volnum, __le32 dirent,
		  const char* name, __u8 ns, __le16 attr)
{
	int result;

	ncp_init_request(server);
	ncp_add_byte(server, 8);
	ncp_add_byte(server, ns);
	ncp_add_byte(server, 0);
	ncp_add_word(server, attr);
	ncp_add_handle_path(server, volnum, dirent, have_dir_base, name);

	result = ncp_request(server, 87);
	ncp_unlock_server(server);
	return result;
}
