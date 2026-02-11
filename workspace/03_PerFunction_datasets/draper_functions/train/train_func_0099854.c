cdiff_cmd_open(const char *cmdstr, struct cdiff_ctx *ctx, char *lbuf, unsigned int lbuflen)
{
	char *db;
	unsigned int i;


    if(!(db = cdiff_token(cmdstr, 1, 1))) {
	logg("!cdiff_cmd_open: Can't get first argument\n");
	return -1;
    }

    if(ctx->open_db) {
	logg("!cdiff_cmd_open: %s not closed before opening %s\n", ctx->open_db, db);
	free(db);
	return -1;
    }

    for(i = 0; i < strlen(db); i++) {
	if((db[i] != '.' && !isalnum(db[i])) || strchr("/\\", db[i])) {
	    logg("!cdiff_cmd_open: Forbidden characters found in database name\n");
	    free(db);
	    return -1;
	}
    }

    ctx->open_db = db;
    return 0;
}
