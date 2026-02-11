write_remote_eir(bdaddr_t *local, bdaddr_t *peer, uint8_t *data,
							uint8_t data_len)
{
	char filename[PATH_MAX + 1], addr[18], str[481];
	int i;

	memset(str, 0, sizeof(str));
	for (i = 0; i < data_len; i++)
		sprintf(str + (i * 2), "%2.2X", data[i]);

	create_filename(filename, PATH_MAX, local, "eir");

	create_file(filename, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

	ba2str(peer, addr);
	return textfile_put(filename, addr, str);
}
