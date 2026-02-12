static avifBool avifParseSampleToChunkBox(avifSampleTable * sampleTable, const uint8_t * raw, size_t rawLen)
{
    BEGIN_STREAM(s, raw, rawLen);

    CHECK(avifROStreamReadAndEnforceVersion(&s, 0));

    uint32_t entryCount;
    CHECK(avifROStreamReadU32(&s, &entryCount));
    for (uint32_t i = 0; i < entryCount; ++i) {
        avifSampleTableSampleToChunk * sampleToChunk = (avifSampleTableSampleToChunk *)avifArrayPushPtr(&sampleTable->sampleToChunks);
        CHECK(avifROStreamReadU32(&s, &sampleToChunk->firstChunk));
        CHECK(avifROStreamReadU32(&s, &sampleToChunk->samplesPerChunk));
        CHECK(avifROStreamReadU32(&s, &sampleToChunk->sampleDescriptionIndex));
    }
    return AVIF_TRUE;
}
