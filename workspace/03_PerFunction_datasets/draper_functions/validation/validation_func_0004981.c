getspulist(unsigned *Nu)
{
	struct	spdet	*result;
	if  (spuf_fid < 0)
		open_file(O_RDWR);
	else
		lseek(spuf_fid, (long) sizeof(struct sphdr), 0);
	lockit(spuf_fid, F_RDLCK);
	result = gallpriv(Nu);
	unlockit(spuf_fid);
	return  result;
}
