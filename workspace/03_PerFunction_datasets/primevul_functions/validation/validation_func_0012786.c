static avifBool avifParseMediaHeaderBox(avifTrack * track, const uint8_t * raw, size_t rawLen)
{
    BEGIN_STREAM(s, raw, rawLen);

    uint8_t version;
    CHECK(avifROStreamReadVersionAndFlags(&s, &version, NULL));

    uint32_t ignored32, mediaTimescale, mediaDuration32;
    uint64_t ignored64, mediaDuration64;
    if (version == 1) {
        CHECK(avifROStreamReadU64(&s, &ignored64));
        CHECK(avifROStreamReadU64(&s, &ignored64));
        CHECK(avifROStreamReadU32(&s, &mediaTimescale));
        CHECK(avifROStreamReadU64(&s, &mediaDuration64));
        track->mediaDuration = mediaDuration64;
    } else if (version == 0) {
        CHECK(avifROStreamReadU32(&s, &ignored32));
        CHECK(avifROStreamReadU32(&s, &ignored32));
        CHECK(avifROStreamReadU32(&s, &mediaTimescale));
        CHECK(avifROStreamReadU32(&s, &mediaDuration32));
        track->mediaDuration = (uint64_t)mediaDuration32;
    } else {

        return AVIF_FALSE;
    }

    track->mediaTimescale = mediaTimescale;
    return AVIF_TRUE;
}
