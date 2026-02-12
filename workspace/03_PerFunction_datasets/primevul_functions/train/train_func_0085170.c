RemoveSocketFiles(void)
{
	ListCell   *l;


	foreach(l, sock_paths)
	{
		char	   *sock_path = (char *) lfirst(l);


		(void) unlink(sock_path);
	}

	sock_paths = NIL;
}
