cgiReadFile (FILE *stream, char *boundary)
{
    char *crlfboundary, *buf;
    size_t boundarylen;
    int c;
    unsigned int pivot;
    char *cp;
    char template[]= "/tmp/cgilibXXXXXX";
    FILE *tmpfile;
    int fd;

    boundarylen = strlen(boundary)+3;
    if ((crlfboundary = (char *)malloc (boundarylen)) == NULL)
	return NULL;
    sprintf (crlfboundary, "\r\n%s", boundary);

    if ((buf = (char *)malloc (boundarylen)) == NULL) {
	free (crlfboundary);
	return NULL;
    }
    memset (buf, 0, boundarylen);
    pivot = 0;

    if ((fd = mkstemp (template)) == -1) {
	free (crlfboundary);
	free (buf);
	return NULL;
    }

    if ((tmpfile = fdopen (fd, "w")) == NULL) {
	free (crlfboundary);
	free (buf);
	unlink (template);
	return NULL;
    }

    while (!feof (stream)) {
	c = fgetc (stream);

	if (c == 0) {
	    if (strlen (buf)) {
		for (cp=buf; *cp; cp++)
		    putc (*cp, tmpfile);
		memset (buf, 0, boundarylen);
		pivot = 0;
	    }
	    putc (c, tmpfile);
	    continue;
	}

	if (strlen (buf)) {
	    if (crlfboundary[pivot+1] == c) {
		buf[++pivot] = c;

		if (strlen (buf) == strlen (crlfboundary))
		    break;
		else
		    continue;
	    } else {
		for (cp=buf; *cp; cp++)
                    putc (*cp, tmpfile);
                memset (buf, 0, boundarylen);
                pivot = 0;
	    }
	}

	if (crlfboundary[0] == c) {
	    buf[0] = c;
	} else {
	    fputc (c, tmpfile);
	}
    }

    if (!feof (stream))
	fgets (buf, boundarylen, stream);

    fclose (tmpfile);

    free (crlfboundary);
    free (buf);

    return strdup (template);
}
