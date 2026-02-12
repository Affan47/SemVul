int rpmPackageFilesInstall(rpmts ts, rpmte te, rpmfiles files,
              rpmpsm psm, char ** failedFile)
{
    FD_t payload = rpmtePayload(te);
    rpmfi fi = NULL;
    rpmfs fs = rpmteGetFileStates(te);
    rpmPlugins plugins = rpmtsPlugins(ts);
    int rc = 0;
    int fx = -1;
    int fc = rpmfilesFC(files);
    int nodigest = (rpmtsFlags(ts) & RPMTRANS_FLAG_NOFILEDIGEST) ? 1 : 0;
    int nofcaps = (rpmtsFlags(ts) & RPMTRANS_FLAG_NOCAPS) ? 1 : 0;
    int firstlinkfile = -1;
    char *tid = NULL;
    struct filedata_s *fdata = xcalloc(fc, sizeof(*fdata));
    struct filedata_s *firstlink = NULL;
    struct diriter_s di = { -1 };


    rasprintf(&tid, ";%08x", (unsigned)rpmtsGetTid(ts));


    fi = rpmfilesIter(files, RPMFI_ITER_FWD);
    while (!rc && (fx = rpmfiNext(fi)) >= 0) {
	struct filedata_s *fp = &fdata[fx];
	if (rpmfiFFlags(fi) & RPMFILE_GHOST)
            fp->action = FA_SKIP;
	else
	    fp->action = rpmfsGetAction(fs, fx);
	fp->skip = XFA_SKIPPING(fp->action);
	if (XFA_CREATING(fp->action) && !S_ISDIR(rpmfiFMode(fi)))
	    fp->suffix = tid;
	fp->fpath = fsmFsPath(fi, fp->suffix);


	rc = rpmfiStat(fi, 1, &fp->sb);


	fp->setmeta = (fp->skip == 0) &&
		      (fp->sb.st_nlink == 1 || fp->action == FA_TOUCH);

	setFileState(fs, fx);
	fsmDebug(fp->fpath, fp->action, &fp->sb);

	fp->stage = FILE_PRE;
    }
    fi = rpmfiFree(fi);

    if (rc)
	goto exit;

    fi = fsmIter(payload, files,
		 payload ? RPMFI_ITER_READ_ARCHIVE : RPMFI_ITER_FWD, &di);

    if (fi == NULL) {
        rc = RPMERR_BAD_MAGIC;
        goto exit;
    }


    while (!rc && (fx = rpmfiNext(fi)) >= 0) {
	struct filedata_s *fp = &fdata[fx];


	if (fp->skip && firstlink && rpmfiArchiveHasContent(fi))
	    fp = firstlink;

        if (!fp->skip) {
	    int fd = -1;

	    if (!fp->suffix && fp != firstlink) {
		rc = fsmBackup(di.dirfd, fi, fp->action);
	    }

	    if (!rc) {
		rc = ensureDir(plugins, rpmfiDN(fi), 0,
				(fp->action == FA_CREATE), 0, &di.dirfd);
	    }


	    rc = rpmpluginsCallFsmFilePre(plugins, fi, fp->fpath,
					  fp->sb.st_mode, fp->action);
	    if (rc)
		goto setmeta;


	    if (!fp->suffix) {
		if (fp->action == FA_TOUCH) {
		    struct stat sb;
		    rc = fsmStat(di.dirfd, fp->fpath, 1, &sb);
		} else {
		    rc = fsmVerify(di.dirfd, fp->fpath, fi);
		}
	    } else {
		rc = RPMERR_ENOENT;
	    }


	    if (rc == RPMERR_ENOENT && fp->action == FA_TOUCH) {
		rpmlog(RPMLOG_DEBUG, "file %s vanished unexpectedly\n",
			fp->fpath);
		fp->action = FA_CREATE;
		fsmDebug(fp->fpath, fp->action, &fp->sb);
	    }


	    if (fp->action == FA_TOUCH)
		goto setmeta;

            if (S_ISREG(fp->sb.st_mode)) {
		if (rc == RPMERR_ENOENT) {
		    rc = fsmMkfile(di.dirfd, fi, fp, files, psm, nodigest,
				   &firstlink, &firstlinkfile, &fd);
		}
            } else if (S_ISDIR(fp->sb.st_mode)) {
                if (rc == RPMERR_ENOENT) {
                    mode_t mode = fp->sb.st_mode;
                    mode &= ~07777;
                    mode |=  00700;
                    rc = fsmMkdir(di.dirfd, fp->fpath, mode);
                }
            } else if (S_ISLNK(fp->sb.st_mode)) {
		if (rc == RPMERR_ENOENT) {
		    rc = fsmSymlink(rpmfiFLink(fi), di.dirfd, fp->fpath);
		}
            } else if (S_ISFIFO(fp->sb.st_mode)) {

                if (rc == RPMERR_ENOENT) {
                    rc = fsmMkfifo(di.dirfd, fp->fpath, 0000);
                }
            } else if (S_ISCHR(fp->sb.st_mode) ||
                       S_ISBLK(fp->sb.st_mode) ||
                       S_ISSOCK(fp->sb.st_mode))
            {
                if (rc == RPMERR_ENOENT) {
                    rc = fsmMknod(di.dirfd, fp->fpath, fp->sb.st_mode, fp->sb.st_rdev);
                }
            } else {

                if (!IS_DEV_LOG(fp->fpath))
                    rc = RPMERR_UNKNOWN_FILETYPE;
            }

	    if (!rc && fd == -1 && !S_ISLNK(fp->sb.st_mode)) {

		fd = fsmOpenat(di.dirfd, fp->fpath,
				fp->suffix ? AT_SYMLINK_NOFOLLOW : 0);
		if (fd < 0)
		    rc = RPMERR_OPEN_FAILED;
	    }

setmeta:
	    if (!rc && fp->setmeta) {
		rc = fsmSetmeta(fd, di.dirfd, fp->fpath,
				fi, plugins, fp->action,
				&fp->sb, nofcaps);
	    }

	    if (fd != firstlinkfile)
		fsmClose(&fd);
	}


	if (rc)
	    *failedFile = xstrdup(fp->fpath);
	else
	    rpmpsmNotify(psm, RPMCALLBACK_INST_PROGRESS, rpmfiArchiveTell(fi));
	fp->stage = FILE_UNPACK;
    }
    fi = fsmIterFini(fi, &di);

    if (!rc && fx < 0 && fx != RPMERR_ITER_END)
	rc = fx;


    fi = fsmIter(NULL, files, RPMFI_ITER_FWD, &di);
    while (!rc && (fx = rpmfiNext(fi)) >= 0) {
	struct filedata_s *fp = &fdata[fx];

	if (!fp->skip) {
	    if (!rc)
		rc = ensureDir(NULL, rpmfiDN(fi), 0, 0, 0, &di.dirfd);


	    if (!rc && fp->suffix)
		rc = fsmBackup(di.dirfd, fi, fp->action);

	    if (!rc)
		rc = fsmCommit(di.dirfd, &fp->fpath, fi, fp->action, fp->suffix);

	    if (!rc)
		fp->stage = FILE_COMMIT;
	    else
		*failedFile = xstrdup(fp->fpath);


	    rpmpluginsCallFsmFilePost(plugins, fi, fp->fpath,
				      fp->sb.st_mode, fp->action, rc);
	}
    }
    fi = fsmIterFini(fi, &di);


    if (rc) {
	fi = fsmIter(NULL, files, RPMFI_ITER_BACK, &di);
	while ((fx = rpmfiNext(fi)) >= 0) {
	    struct filedata_s *fp = &fdata[fx];


	    if (ensureDir(NULL, rpmfiDN(fi), 0, 0, 1, &di.dirfd))
		continue;

	    if (fp->stage > FILE_NONE && !fp->skip) {
		(void) fsmRemove(di.dirfd, fp->fpath, fp->sb.st_mode);
	    }
	}
    }

    rpmswAdd(rpmtsOp(ts, RPMTS_OP_UNCOMPRESS), fdOp(payload, FDSTAT_READ));
    rpmswAdd(rpmtsOp(ts, RPMTS_OP_DIGEST), fdOp(payload, FDSTAT_DIGEST));

exit:
    fi = fsmIterFini(fi, &di);
    Fclose(payload);
    free(tid);
    for (int i = 0; i < fc; i++)
	free(fdata[i].fpath);
    free(fdata);

    return rc;
}
