_tarPositionTo(ArchiveHandle *AH, const char *filename)
{
	lclContext *ctx = (lclContext *) AH->formatData;
	TAR_MEMBER *th = pg_malloc0(sizeof(TAR_MEMBER));
	char		c;
	char		header[512];
	size_t		i,
				len,
				blks;
	int			id;

	th->AH = AH;


	if (ctx->tarFHpos != 0)
	{
		char		buf1[100],
					buf2[100];

		snprintf(buf1, sizeof(buf1), INT64_FORMAT, (int64) ctx->tarFHpos);
		snprintf(buf2, sizeof(buf2), INT64_FORMAT, (int64) ctx->tarNextMember);
		ahlog(AH, 4, "moving from position %s to next member at file position %s\n",
			  buf1, buf2);

		while (ctx->tarFHpos < ctx->tarNextMember)
			_tarReadRaw(AH, &c, 1, NULL, ctx->tarFH);
	}

	{
		char		buf[100];

		snprintf(buf, sizeof(buf), INT64_FORMAT, (int64) ctx->tarFHpos);
		ahlog(AH, 4, "now at file position %s\n", buf);
	}


	if (!_tarGetHeader(AH, th))
	{
		if (filename)
			exit_horribly(modulename, "could not find header for file \"%s\" in tar archive\n", filename);
		else
		{


			free(th);
			return NULL;
		}
	}

	while (filename != NULL && strcmp(th->targetFile, filename) != 0)
	{
		ahlog(AH, 4, "skipping tar member %s\n", th->targetFile);

		id = atoi(th->targetFile);
		if ((TocIDRequired(AH, id) & REQ_DATA) != 0)
			exit_horribly(modulename, "restoring data out of order is not supported in this archive format: "
						  "\"%s\" is required, but comes before \"%s\" in the archive file.\n",
						  th->targetFile, filename);


		len = ((th->fileLen + 511) & ~511);
		blks = len >> 9;

		for (i = 0; i < blks; i++)
			_tarReadRaw(AH, &header[0], 512, NULL, ctx->tarFH);

		if (!_tarGetHeader(AH, th))
			exit_horribly(modulename, "could not find header for file \"%s\" in tar archive\n", filename);
	}

	ctx->tarNextMember = ctx->tarFHpos + ((th->fileLen + 511) & ~511);
	th->pos = 0;

	return th;
}
