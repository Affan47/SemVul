static avifBool avifParseAV1CodecConfigurationBox(const uint8_t * raw, size_t rawLen, avifCodecConfigurationBox * av1C)
{
    BEGIN_STREAM(s, raw, rawLen);

    uint8_t markerAndVersion = 0;
    CHECK(avifROStreamRead(&s, &markerAndVersion, 1));
    uint8_t seqProfileAndIndex = 0;
    CHECK(avifROStreamRead(&s, &seqProfileAndIndex, 1));
    uint8_t rawFlags = 0;
    CHECK(avifROStreamRead(&s, &rawFlags, 1));

    if (markerAndVersion != 0x81) {

        return AVIF_FALSE;
    }

    av1C->seqProfile = (seqProfileAndIndex >> 5) & 0x7;
    av1C->seqLevelIdx0 = (seqProfileAndIndex >> 0) & 0x1f;
    av1C->seqTier0 = (rawFlags >> 7) & 0x1;
    av1C->highBitdepth = (rawFlags >> 6) & 0x1;
    av1C->twelveBit = (rawFlags >> 5) & 0x1;
    av1C->monochrome = (rawFlags >> 4) & 0x1;
    av1C->chromaSubsamplingX = (rawFlags >> 3) & 0x1;
    av1C->chromaSubsamplingY = (rawFlags >> 2) & 0x1;
    av1C->chromaSamplePosition = (rawFlags >> 0) & 0x3;
    return AVIF_TRUE;
}
