convert_R8G8B8toA1R5G5B5(const void* sP, s32 sN, void* dP)
{
	u8 * sB = (u8 *)sP;
	u16* dB = (u16*)dP;

	for (s32 x = 0; x < sN; ++x)
	{
		s32 r = sB[0] >> 3;
		s32 g = sB[1] >> 3;
		s32 b = sB[2] >> 3;

		dB[0] = (0x8000) | (r << 10) | (g << 5) | (b);

		sB += 3;
		dB += 1;
	}
}
