AllocateCompressor(int compression, WriteFunc writeF)
{
	CompressorState *cs;
	CompressionAlgorithm alg;
	int level;

	ParseCompressionOption(compression, &alg, &level);

#ifndef HAVE_LIBZ
	if (alg == COMPR_ALG_LIBZ)
		die_horribly(NULL, modulename, "not built with zlib support\n");
#endif

	cs = (CompressorState *) calloc(1, sizeof(CompressorState));
	if (cs == NULL)
		die_horribly(NULL, modulename, "out of memory\n");
	cs->writeF = writeF;
	cs->comprAlg = alg;


#ifdef HAVE_LIBZ
	if (alg == COMPR_ALG_LIBZ)
		InitCompressorZlib(cs, level);
#endif

	return cs;
}
