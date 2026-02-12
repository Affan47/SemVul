static int fsmDoMkDir(rpmPlugins plugins, int dirfd, const char *dn,
			int owned, mode_t mode)
{
    int rc;
    rpmFsmOp op = (FA_CREATE);
    if (!owned)
	op |= FAF_UNOWNED;


    rc = rpmpluginsCallFsmFilePre(plugins, NULL, dn, mode, op);

    if (!rc)
	rc = fsmMkdir(dirfd, dn, mode);

    if (!rc) {
	rc = rpmpluginsCallFsmFilePrepare(plugins, NULL, dn, dn, mode, op);
    }


    rpmpluginsCallFsmFilePost(plugins, NULL, dn, mode, op, rc);

    if (!rc) {
	rpmlog(RPMLOG_DEBUG,
		"%s directory created with perms %04o\n",
		dn, (unsigned)(mode & 07777));
    }

    return rc;
}
