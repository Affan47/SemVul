access( const char *n, mode_t mode )
{
	pfs_name pname;
	int result = -1;

	if(resolve_name(n,&pname)) {
		result = pname.service->access(&pname,mode);
	}

	return result;
}
