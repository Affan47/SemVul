rpmRC rpmReadPackageFile(rpmts ts, FD_t fd, const char * fn, Header * hdrp)
{
    rpmRC rc;
    rpmVSFlags vsflags = rpmtsVSFlags(ts);
    rpmKeyring keyring = rpmtsGetKeyring(ts, 1);
    unsigned int keyid = 0;
    char *msg = NULL;

    if (fn == NULL)
	fn = Fdescr(fd);

    rc = rpmpkgRead(keyring, vsflags, fd, hdrp, &keyid, &msg);

    switch (rc) {
    case RPMRC_OK:
	rpmlog(RPMLOG_DEBUG, "%s: %s\n", fn, msg);
	break;
    case RPMRC_NOTTRUSTED:
    case RPMRC_NOKEY:

    {	int lvl = (stashKeyid(keyid) ? RPMLOG_DEBUG : RPMLOG_WARNING);
	rpmlog(lvl, "%s: %s\n", fn, msg);
    }	break;
    case RPMRC_NOTFOUND:

	if (msg)
	    rpmlog(RPMLOG_WARNING, "%s: %s\n", fn, msg);
	break;
    default:
    case RPMRC_FAIL:
	rpmlog(RPMLOG_ERR, "%s: %s\n", fn, msg);
	break;
    }
    rpmKeyringFree(keyring);
    free(msg);

    return rc;
}
