isModifiedByte(FileOfs o)
{
	ObjHandle h = findArea(o);
	FileArea *fa = (FileArea*)mods.get(h);
	if (!fa) return true;
	if (fa->getObjectID() == OBJID_MFA) {
		ModifiedFileArea *mfa = (ModifiedFileArea*)fa;
		int pg_ofs = o - fa->start;
		byte b;
		mFile->seek(o);
		mFile->readx(&b, 1);
		return mfa->buf[pg_ofs] != b;
	} else if (fa->getObjectID() == OBJID_CFA) {
		CopiedFileArea *cfa = (CopiedFileArea*)fa;
		if (cfa->src_start == cfa->start) return false;
		int pg_ofs = o - fa->start;
		byte b1, b2;
		mFile->seek(o);
		mFile->readx(&b1, 1);
		mFile->seek(cfa->src_start + pg_ofs);
		mFile->readx(&b2, 1);
		return (b1 != b2);
	}
	return false;
}
