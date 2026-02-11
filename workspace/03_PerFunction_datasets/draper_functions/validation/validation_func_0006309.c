LogRoll(Log *logPtr)
{
    int 	status;

    status = NS_OK;
    (void) LogClose(logPtr);
    if (access(logPtr->file, F_OK) == 0) {
    	if (logPtr->rollfmt == NULL) {
	    status = Ns_RollFile(logPtr->file, logPtr->maxbackup);
	} else {
	    Ns_DString  ds;
	    time_t 	now;
	    struct tm  *ptm;
	    char 	timeBuf[512];

	    now = time(NULL);
	    ptm = ns_localtime(&now);
	    strftime(timeBuf, 512, logPtr->rollfmt, ptm);
	    Ns_DStringInit(&ds);
	    Ns_DStringVarAppend(&ds, logPtr->file, ".", timeBuf, NULL);
	    if (access(ds.string, F_OK) == 0) {
		status = Ns_RollFile(ds.string, logPtr->maxbackup);
	    } else if (errno != ENOENT) {
		Ns_Log(Error, "nslog: access(%s, F_OK) failed: '%s'",
	      	       ds.string, strerror(errno));
		status = NS_ERROR;
	    }
	    if (status == NS_OK && rename(logPtr->file, ds.string) != 0) {
	    	Ns_Log(Error, "nslog: rename(%s, %s) failed: '%s'",
		    logPtr->file, ds.string, strerror(errno));
		status = NS_ERROR;
	    }
	    Ns_DStringFree(&ds);
	    if (status == NS_OK) {
		status = Ns_PurgeFiles(logPtr->file, logPtr->maxbackup);
	    }
	}
    }
    status = LogOpen(logPtr);
    return status;
}
