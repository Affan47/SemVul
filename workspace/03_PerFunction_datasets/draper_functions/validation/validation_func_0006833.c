deleteUser(FILE* db, const char* user)
{
    const char* templ = "/" FAX_TMPDIR "/udelXXXXXX";
    char* buff = strcpy(new char[strlen(templ) + 1], templ);
    int fd = Sys::mkstemp(buff);
    fxStr tfile = buff;
    delete [] buff;
    FILE* ftmp;
    if (fd < 0 || (ftmp = fdopen(fd, "w")) == NULL) {
        reply(550, "Error creating temp file %s: %s.",
	        (const char*)tfile, strerror(errno));
        return (false);
    }


    bool found = false;
    rewind(db);
    char line[8*1024];
    while (fgets(line, sizeof (line)-1, db)) {
	if (line[0] != '!') {
	    const char* cp;
	    for (cp = line; *cp && *cp != '\n' && *cp != ':'; cp++)
		;
	    if (strncmp(user, line, cp-line) == 0) {
		found = true;
		break;
	    }
	}
	fputs(line, ftmp);
    }
    int cc;
    while ((cc = fread(line, 1, sizeof (line), db)) > 0)
	fwrite(line, cc, 1, ftmp);
    bool ioError = (fclose(ftmp) != 0);
    if (found) {
	if (ioError)
	    perror_reply(550, "I/O error", errno);
	else if (Sys::rename(tfile, fixPathname(userAccessFile)) < 0)
	    perror_reply(550, "Rename of temp file failed", errno);
	else {
	    return (true);
        }
    } else
	reply(500, "User %s not found in access file.", user);
    (void) Sys::unlink(tfile);
    return (false);
}
