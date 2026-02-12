GF_Err stbl_GetPaddingBits(GF_PaddingBitsBox *padb, u32 SampleNumber, u8 *PadBits)
{
	if (!PadBits) return GF_BAD_PARAM;
	*PadBits = 0;
	if (!padb || !padb->padbits) return GF_OK;

	if (padb->SampleCount < SampleNumber) return GF_OK;
	*PadBits = padb->padbits[SampleNumber-1];
	return GF_OK;
}
