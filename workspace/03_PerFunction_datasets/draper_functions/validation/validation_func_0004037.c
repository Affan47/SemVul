is_in_val_tags (DBM **idb, const char *name)
{
    DBM *db = NULL;
    char *valtags_filename;
    datum mytag;
    int status;


    if (readonlyfs)
      return 1;


    mytag.dptr = (char *)name;
    mytag.dsize = strlen (name);

    valtags_filename = Xasprintf ("%s/%s/%s", current_parsed_root->directory,
				  CVSROOTADM, CVSROOTADM_VALTAGS);

    if (idb)
    {
	mode_t omask;

	omask = umask (cvsumask);
	db = dbm_open (valtags_filename, O_RDWR | O_CREAT, 0666);
	umask (omask);

	if (!db)
	{

	    error (0, errno, "warning: cannot open `%s' read/write",
		   valtags_filename);
	    *idb = NULL;
	    return 1;
	}

	*idb = db;
    }
    else
    {
	db = dbm_open (valtags_filename, O_RDONLY, 0444);
	if (!db && !existence_error (errno))
	    error (1, errno, "cannot read %s", valtags_filename);
    }


    status = 0;
    if (db)
    {
	datum val;

	val = dbm_fetch (db, mytag);
	if (val.dptr != NULL)

	    status = 1;


	if (!idb) dbm_close (db);
    }

    free (valtags_filename);
    return status;
}
