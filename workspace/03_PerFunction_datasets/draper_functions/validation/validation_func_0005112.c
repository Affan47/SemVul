DXLoadMDFFile(char *filename)
{
    int fd;
    int len, rlen;
    int rc = ERROR;
    char *foundname = NULL;
    char *cp = NULL;

    if (_dxf_fileSearch(filename, &foundname, "mdf", "DXMODULES") == ERROR)
	return ERROR;

    fd = open(foundname, O_RDONLY);
    if (fd < 0) {
	DXSetError(ERROR_DATA_INVALID, "cannot open %s as MDF file", foundname);
	goto error;
    }

    len = lseek(fd, 0, 2);
    if (len <= 0) {
	DXSetError(ERROR_DATA_INVALID, "error reading from %s", foundname);
	goto error;
    }
    lseek(fd, 0, 0);

    cp = (char *)DXAllocate(len+1);
    if (!cp)
	goto error;

    rlen = read(fd, cp, len);
    if (rlen != len) {
	DXSetError(ERROR_DATA_INVALID, "error reading from %s", foundname);
	goto error;
    }
    cp[len] = '\0';

    close (fd);

    rc = ExParseMDF(cp);

  error:
    DXFree((Pointer)cp);
    DXFree((Pointer)foundname);
    return rc;
}
