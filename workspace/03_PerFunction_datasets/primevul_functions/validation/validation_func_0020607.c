vim_deltempdir(void)
{
    if (vim_tempdir != NULL)
    {

	gettail(vim_tempdir)[-1] = NUL;
	delete_recursive(vim_tempdir);
	vim_free(vim_tempdir);
	vim_tempdir = NULL;
    }
}
