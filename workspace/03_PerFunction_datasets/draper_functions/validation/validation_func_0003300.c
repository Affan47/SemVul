lm_error(struct MF *mf, char *s)
{
	struct MFX *mfx = (struct MFX *) mf;

	if (mfx->err == GN_ERR_NONE)
		mfx->err = GN_ERR_WRONGDATAFORMAT;
	fprintf(stderr, "%s\n", s);
}
