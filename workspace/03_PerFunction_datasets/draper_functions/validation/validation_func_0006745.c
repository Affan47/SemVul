aim_oft_createinfo(aim_session_t *sess,
	const fu8_t *cookie, const char *sn, const char *ip, fu16_t port,
	fu32_t size, fu32_t modtime, char *filename)
{
	struct aim_oft_info *new;

	if (!sess)
		return NULL;

	if (!(new = (struct aim_oft_info *)calloc(1,
				sizeof(struct aim_oft_info))))
		return NULL;

	new->sess = sess;
	if (cookie)
		memcpy(new->cookie, cookie, 8);
	if (ip)
		new->clientip = strdup(ip);
	if (sn)
		new->sn = strdup(sn);
	new->port = port;
	new->fh.totfiles = 1;
	new->fh.filesleft = 1;
	new->fh.totparts = 1;
	new->fh.partsleft = 1;
	new->fh.totsize = size;
	new->fh.size = size;
	new->fh.modtime = modtime;
	new->fh.checksum = 0xffff0000;
	new->fh.rfrcsum = 0xffff0000;
	new->fh.rfcsum = 0xffff0000;
	new->fh.recvcsum = 0xffff0000;
	strncpy(new->fh.idstring, "OFT_Windows ICBMFT V1.1 32", 31);
	if (filename)
		strncpy(new->fh.name, filename, 63);

	new->next = sess->oft_info;
	sess->oft_info = new;

	return new;
}
