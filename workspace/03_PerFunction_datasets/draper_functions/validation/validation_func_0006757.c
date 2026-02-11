DGifDecompressInput(GifFilePrivateType *Private, int *Code)
{
    GifByteType NextByte;
    static unsigned int CodeMasks[] = {
	0x0000, 0x0001, 0x0003, 0x0007,
	0x000f, 0x001f, 0x003f, 0x007f,
	0x00ff, 0x01ff, 0x03ff, 0x07ff,
	0x0fff
    };

    while (Private->CrntShiftState < Private->RunningBits) {

	if (DGifBufferedInput(Private->File, Private->Buf, &NextByte)
	    == GIF_ERROR) {
	    return GIF_ERROR;
	}
	Private->CrntShiftDWord |=
		((unsigned long) NextByte) << Private->CrntShiftState;
	Private->CrntShiftState += 8;
    }
    *Code = Private->CrntShiftDWord & CodeMasks[Private->RunningBits];

    Private->CrntShiftDWord >>= Private->RunningBits;
    Private->CrntShiftState -= Private->RunningBits;


    if (++Private->RunningCode > Private->MaxCode1 &&
	Private->RunningBits < LZ_BITS) {
	Private->MaxCode1 <<= 1;
	Private->RunningBits++;
    }
    return GIF_OK;
}
