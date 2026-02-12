TouchSocketFiles(void)
{
	ListCell   *l;


	foreach(l, sock_paths)
	{
		char	   *sock_path = (char *) lfirst(l);


		(void) utime(sock_path, NULL);
	}
}
