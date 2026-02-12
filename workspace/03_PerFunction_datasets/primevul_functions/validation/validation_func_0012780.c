static avifBool avifParseTrackHeaderBox(avifTrack * track, const uint8_t * raw, size_t rawLen)
{
    BEGIN_STREAM(s, raw, rawLen);

    uint8_t version;
    CHECK(avifROStreamReadVersionAndFlags(&s, &version, NULL));

    uint32_t ignored32, trackID;
    uint64_t ignored64;
    if (version == 1) {
        CHECK(avifROStreamReadU64(&s, &ignored64));
        CHECK(avifROStreamReadU64(&s, &ignored64));
        CHECK(avifROStreamReadU32(&s, &trackID));
        CHECK(avifROStreamReadU32(&s, &ignored32));
        CHECK(avifROStreamReadU64(&s, &ignored64));
    } else if (version == 0) {
        CHECK(avifROStreamReadU32(&s, &ignored32));
        CHECK(avifROStreamReadU32(&s, &ignored32));
        CHECK(avifROStreamReadU32(&s, &trackID));
        CHECK(avifROStreamReadU32(&s, &ignored32));
        CHECK(avifROStreamReadU32(&s, &ignored32));
    } else {

        return AVIF_FALSE;
    }


    CHECK(avifROStreamSkip(&s, 52));

    uint32_t width, height;
    CHECK(avifROStreamReadU32(&s, &width));
    CHECK(avifROStreamReadU32(&s, &height));
    track->width = width >> 16;
    track->height = height >> 16;


    track->id = trackID;
    return AVIF_TRUE;
}
