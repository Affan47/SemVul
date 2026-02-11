_ReadByte(ArchiveHandle *AH)
{
	lclContext *ctx = (lclContext *) AH->formatData;
	int			res;

	res = getc(AH->FH);
	if (res == EOF)
		die_horribly(AH, modulename, "unexpected end of file\n");
	ctx->filePos += 1;
	return res;
}
