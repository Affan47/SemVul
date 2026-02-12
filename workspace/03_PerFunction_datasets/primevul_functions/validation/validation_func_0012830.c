static avifBool avifCodecDecodeInputGetSamples(avifCodecDecodeInput * decodeInput, avifSampleTable * sampleTable, avifROData * rawInput)
{
    uint32_t sampleSizeIndex = 0;
    for (uint32_t chunkIndex = 0; chunkIndex < sampleTable->chunks.count; ++chunkIndex) {
        avifSampleTableChunk * chunk = &sampleTable->chunks.chunk[chunkIndex];


        uint32_t sampleCount = 0;
        for (int sampleToChunkIndex = sampleTable->sampleToChunks.count - 1; sampleToChunkIndex >= 0; --sampleToChunkIndex) {
            avifSampleTableSampleToChunk * sampleToChunk = &sampleTable->sampleToChunks.sampleToChunk[sampleToChunkIndex];
            if (sampleToChunk->firstChunk <= (chunkIndex + 1)) {
                sampleCount = sampleToChunk->samplesPerChunk;
                break;
            }
        }
        if (sampleCount == 0) {

            return AVIF_FALSE;
        }

        uint64_t sampleOffset = chunk->offset;
        for (uint32_t sampleIndex = 0; sampleIndex < sampleCount; ++sampleIndex) {
            uint32_t sampleSize = sampleTable->allSamplesSize;
            if (sampleSize == 0) {
                if (sampleSizeIndex >= sampleTable->sampleSizes.count) {

                    return AVIF_FALSE;
                }
                avifSampleTableSampleSize * sampleSizePtr = &sampleTable->sampleSizes.sampleSize[sampleSizeIndex];
                sampleSize = sampleSizePtr->size;
            }

            avifDecodeSample * sample = (avifDecodeSample *)avifArrayPushPtr(&decodeInput->samples);
            sample->data.data = rawInput->data + sampleOffset;
            sample->data.size = sampleSize;
            sample->sync = AVIF_FALSE;

            if ((sampleOffset + sampleSize) > (uint64_t)rawInput->size) {
                return AVIF_FALSE;
            }

            sampleOffset += sampleSize;
            ++sampleSizeIndex;
        }
    }


    for (uint32_t syncSampleIndex = 0; syncSampleIndex < sampleTable->syncSamples.count; ++syncSampleIndex) {
        uint32_t frameIndex = sampleTable->syncSamples.syncSample[syncSampleIndex].sampleNumber - 1;
        if (frameIndex < decodeInput->samples.count) {
            decodeInput->samples.sample[frameIndex].sync = AVIF_TRUE;
        }
    }


    if (decodeInput->samples.count > 0) {
        decodeInput->samples.sample[0].sync = AVIF_TRUE;
    }
    return AVIF_TRUE;
}
