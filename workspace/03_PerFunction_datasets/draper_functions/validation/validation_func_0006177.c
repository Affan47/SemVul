getnext(register DBM *db)
{
	datum key;

	for (;;) {
		db->keyptr++;
		key = getnkey(db->pagbuf, db->keyptr);
		if (key.dptr != NULL)
			return key;


		db->keyptr = 0;
		if (db->pagbno != db->blkptr++)
			if (lseek(db->pagf, OFF_PAG(db->blkptr), SEEK_SET) < 0)
				break;
		db->pagbno = db->blkptr;
		if (read(db->pagf, db->pagbuf, PBLKSIZ) <= 0)
			break;
		if (!chkpage(db->pagbuf)) {
			break;
		}
	}

	return ioerr(db), nullitem;
}
