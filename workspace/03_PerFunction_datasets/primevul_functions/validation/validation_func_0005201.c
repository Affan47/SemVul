GF_Err stbl_SetSampleCTS(GF_SampleTableBox *stbl, u32 sampleNumber, s32 offset)
{
	GF_CompositionOffsetBox *ctts = stbl->CompositionOffset;

	assert(ctts->unpack_mode);


	if (ctts->w_LastSampleNumber < sampleNumber) {

		while (ctts->w_LastSampleNumber + 1 != sampleNumber) {
			GF_Err e = AddCompositionOffset(ctts, 0);
			if (e) return e;
		}
		return AddCompositionOffset(ctts, offset);
	}
	if (offset<0) ctts->version=1;
	ctts->entries[sampleNumber-1].decodingOffset = offset;
	return GF_OK;
}
