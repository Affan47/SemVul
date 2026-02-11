Find_Names (char *repository, int which, int aflag, List **optentries)
{
    List *entries;
    List *files;


    files = getlist ();


    if (which & W_LOCAL)
    {

	entries = Entries_Open (aflag, NULL);
	if (entries != NULL)
	{

	    (void) walklist (entries, add_entries_proc, files);


	    if (optentries != NULL)
		*optentries = entries;
	    else
		Entries_Close (entries);
	}
    }

    if ((which & W_REPOS) && repository && !isreadable (CVSADM_ENTSTAT))
    {

	if (find_rcs (repository, files) != 0)
	{
	    error (0, errno, "cannot open directory %s",
		   primary_root_inverse_translate (repository));
	    goto error_exit;
	}


	if (which & W_ATTIC)
	{
	    char *dir = Xasprintf ("%s/%s", repository, CVSATTIC);
	    if (find_rcs (dir, files) != 0
		&& !existence_error (errno))


		error (1, errno, "cannot open directory %s",
		       primary_root_inverse_translate (dir));
	    free (dir);
	}
    }


    sortlist (files, fsortcmp);
    return files;
 error_exit:
    dellist (&files);
    return NULL;
}
