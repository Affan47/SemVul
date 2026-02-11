Parse_MIME_FromFileName(const char *fname)
    {
    FILE *fp = fopen(fname,"r");
    if (fp) {
	VObject* o = Parse_MIME_FromFile(fp);
	fclose(fp);
	return o;
	}
    else {
	char msg[255];
	snprintf(msg, sizeof(msg), "can't open file '%s' for reading\n", fname);
	mime_error_(msg);
	return 0;
	}
    }
