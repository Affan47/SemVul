hts_close(htsFile *fp)
{
	int ret, save;

	if (fp->is_bin || (fp->is_write && fp->is_compressed==1)) {
		ret = bgzf_close(fp->fp.bgzf);
	} else if (fp->is_cram) {
		ret = cram_close(fp->fp.cram);
	} else if (fp->is_kstream) {
	#if KS_BGZF
		BGZF *gzfp = ((kstream_t*)fp->fp.voidp)->f;
		ret = bgzf_close(gzfp);
	#else
		gzFile gzfp = ((kstream_t*)fp->fp.voidp)->f;
		ret = gzclose(gzfp);
	#endif
		ks_destroy((kstream_t*)fp->fp.voidp);
	} else {
		ret = hclose(fp->fp.hfile);
	}

	save = errno;
	free(fp->fn);
	free(fp->fn_aux);
    free(fp->line.s);
	free(fp);
	errno = save;
	return ret;
}
