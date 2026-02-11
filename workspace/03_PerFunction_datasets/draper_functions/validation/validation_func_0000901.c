intif_mail_checkmail(int account_id,struct mail_data *md)
{
	int size;

	if (inter_fd < 0)
		return -1;

	size = sizeof(struct mail_data);
	WFIFOW(inter_fd,0) = 0x304e;
	WFIFOW(inter_fd,2) = 8+size;
	WFIFOL(inter_fd,4) = account_id;
	memcpy(WFIFOP(inter_fd,8), md, size);
	WFIFOSET(inter_fd, 8+size);

	return 0;
}
