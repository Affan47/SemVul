int rpmPackageFilesRemove(rpmts ts, rpmte te, rpmfiles files,
              rpmpsm psm, char ** failedFile)
{
    struct diriter_s di = { -1 };
    rpmfi fi = fsmIter(NULL, files, RPMFI_ITER_BACK, &di);
    rpmfs fs = rpmteGetFileStates(te);
    rpmPlugins plugins = rpmtsPlugins(ts);
    int fc = rpmfilesFC(files);
    int fx = -1;
    struct filedata_s *fdata = xcalloc(fc, sizeof(*fdata));
    int rc = 0;

    while (!rc && (fx = rpmfiNext(fi)) >= 0) {
	struct filedata_s *fp = &fdata[fx];
	fp->action = rpmfsGetAction(fs, rpmfiFX(fi));

	if (XFA_SKIPPING(fp->action))
	    continue;

	fp->fpath = fsmFsPath(fi, NULL);

	if (ensureDir(NULL, rpmfiDN(fi), 0, 0, 1, &di.dirfd))
	    continue;

	rc = fsmStat(di.dirfd, fp->fpath, 1, &fp->sb);

	fsmDebug(fp->fpath, fp->action, &fp->sb);


	rc = rpmpluginsCallFsmFilePre(plugins, fi, fp->fpath,
				      fp->sb.st_mode, fp->action);

	rc = fsmBackup(di.dirfd, fi, fp->action);


        if (fp->action == FA_ERASE) {
	    int missingok = (rpmfiFFlags(fi) & (RPMFILE_MISSINGOK | RPMFILE_GHOST));

	    rc = fsmRemove(di.dirfd, fp->fpath, fp->sb.st_mode);


	    if (rc == RPMERR_ENOENT && missingok) {
		rc = 0;
	    }


	    if (rc == RPMERR_ENOTEMPTY) {
		rc = 0;
	    }

	    if (rc) {
		int lvl = strict_erasures ? RPMLOG_ERR : RPMLOG_WARNING;
		rpmlog(lvl, _("%s %s: remove failed: %s\n"),
			S_ISDIR(fp->sb.st_mode) ? _("directory") : _("file"),
			fp->fpath, strerror(errno));
            }
        }


	rpmpluginsCallFsmFilePost(plugins, fi, fp->fpath,
				  fp->sb.st_mode, fp->action, rc);


        if (!strict_erasures) rc = 0;

	if (rc)
	    *failedFile = xstrdup(fp->fpath);

	if (rc == 0) {


	    rpm_loff_t amount = rpmfiFC(fi) - rpmfiFX(fi);
	    rpmpsmNotify(psm, RPMCALLBACK_UNINST_PROGRESS, amount);
	}
    }

    for (int i = 0; i < fc; i++)
	free(fdata[i].fpath);
    free(fdata);
    fsmIterFini(fi, &di);

    return rc;
}
