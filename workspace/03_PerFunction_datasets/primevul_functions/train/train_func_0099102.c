unsetspec(struct tbl *vp)
{


	switch (special(vp->name)) {
	case V_IFS:
		setctypes(TC_IFSWS, C_IFS);
		ifs0 = ' ';
		break;
	case V_PATH:
		if (path)
			afree(path, APERM);
		strdupx(path, def_path, APERM);

		flushcom(true);
		break;
	case V_TMPDIR:

		if (tmpdir) {
			afree(tmpdir, APERM);
			tmpdir = NULL;
		}
		break;
	case V_LINENO:
	case V_RANDOM:
	case V_SECONDS:
	case V_TMOUT:

		unspecial(vp->name);
		break;
	}
}
