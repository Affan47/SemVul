disk_setwriteprotect (struct uae_prefs *p, int num, const TCHAR *name, bool writeprotected)
{
	int needwritefile, oldprotect;
	struct zfile *zf1, *zf2;
	bool wrprot1, wrprot2;
	int i;
	TCHAR *name2;
	drive_type drvtype;

	oldprotect = diskfile_iswriteprotect (p, name, &needwritefile, &drvtype);
	DISK_validate_filename (p, name, 1, &wrprot1, NULL, &zf1);
	if (!zf1)
		return 0;
	if (wrprot1 && p->floppy_read_only)
		return 0;
	if (zfile_iscompressed (zf1))
		wrprot1 = 1;
	zfile_fclose (zf1);
	zf2 = getwritefile (p, name, &wrprot2);
	name2 = DISK_get_saveimagepath (name);

	if (needwritefile && zf2 == 0)
		disk_creatediskfile (name2, 1, drvtype, NULL, false, false, NULL);
	zfile_fclose (zf2);
	if (writeprotected && iswritefileempty (p, name)) {
		for (i = 0; i < MAX_FLOPPY_DRIVES; i++) {
			if (!_tcscmp (name, floppy[i].newname))
				drive_eject (&floppy[i]);
		}
		_wunlink (name2);
	}

	if (!needwritefile)
		diskfile_readonly (name, writeprotected);
	diskfile_readonly (name2, writeprotected);
	DISK_reinsert (num);
	return 1;
}
