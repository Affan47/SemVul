pfs_md5( const char *path, unsigned char *digest )
{
	BEGIN
	debug(D_LIBCALL,"md5 %s",path);
	result = pfs_current->table->md5(path,digest);
	END
}
