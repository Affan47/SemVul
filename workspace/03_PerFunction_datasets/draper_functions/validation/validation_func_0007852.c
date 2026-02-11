zReadGTFConvInfo(FILE* stream, zGTFConvInfo *conv) {
	char    line[2048], model[128], gtff[128];
	gtf_t   gtf_type;
	zStrIdx stridx;
	int     number_read;

	zInitGTFConvInfo(conv);
	while (fgets(line, sizeof(line)-1, stream) != NULL) {
		line[sizeof(line)-1] = '\0';

		number_read = sscanf(line, "%127s => %127s", model, gtff);
		model[sizeof(model)-1] = '\0';
		gtff [sizeof(gtff) -1] = '\0';

		if (EOF == number_read) continue;
		if (2 != number_read) return;
		stridx   = zChar2StrIdx(model);
		gtf_type = zText2GTF(gtff);
		if (stridx < 0 || stridx >= conv->maxStrIdx) {
			zWarn("The model type %s is unrecognized", model);
		} else if (gtf_type >= zGTF_UNDEF) {
			zWarn("GTF feature %s is not allowed", gtff);
		} else {

			conv->gtft2StrIdx[gtf_type] = stridx;
			conv->strIdx2gtft[stridx]   = gtf_type;
		}
	}
}
