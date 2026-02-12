int afIdentifyFD (int fd)
{
	FILE		*fp;
	AFvirtualfile	*vf;
	int		result;


	fd = dup(fd);
	vf = new File(fd, File::ReadAccess);

	result = _af_identify(vf, NULL);

	af_fclose(vf);

	return result;
}
