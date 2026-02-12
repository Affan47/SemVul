readSampleCountForLineBlock(InputStreamMutex* streamData,
                            DeepScanLineInputFile::Data* data,
                            int lineBlockId)
{
    streamData->is->seekg(data->lineOffsets[lineBlockId]);

    if (isMultiPart(data->version))
    {
        int partNumber;
        OPENEXR_IMF_INTERNAL_NAMESPACE::Xdr::read <OPENEXR_IMF_INTERNAL_NAMESPACE::StreamIO> (*streamData->is, partNumber);

        if (partNumber != data->partNumber)
            throw IEX_NAMESPACE::ArgExc("Unexpected part number.");
    }

    int minY;
    OPENEXR_IMF_INTERNAL_NAMESPACE::Xdr::read <OPENEXR_IMF_INTERNAL_NAMESPACE::StreamIO> (*streamData->is, minY);


    if (minY != data->minY + lineBlockId * data->linesInBuffer)
        throw IEX_NAMESPACE::ArgExc("Unexpected data block y coordinate.");

    int maxY;
    maxY = min(minY + data->linesInBuffer - 1, data->maxY);

    uint64_t sampleCountTableDataSize;
    OPENEXR_IMF_INTERNAL_NAMESPACE::Xdr::read <OPENEXR_IMF_INTERNAL_NAMESPACE::StreamIO> (*streamData->is, sampleCountTableDataSize);


    if(sampleCountTableDataSize>static_cast<uint64_t>(data->maxSampleCountTableSize))
    {
        THROW (IEX_NAMESPACE::ArgExc, "Bad sampleCountTableDataSize read from chunk "<< lineBlockId << ": expected " << data->maxSampleCountTableSize << " or less, got "<< sampleCountTableDataSize);
    }

    uint64_t packedDataSize;
    uint64_t unpackedDataSize;
    OPENEXR_IMF_INTERNAL_NAMESPACE::Xdr::read <OPENEXR_IMF_INTERNAL_NAMESPACE::StreamIO> (*streamData->is, packedDataSize);
    OPENEXR_IMF_INTERNAL_NAMESPACE::Xdr::read <OPENEXR_IMF_INTERNAL_NAMESPACE::StreamIO> (*streamData->is, unpackedDataSize);


    int compressorMaxDataSize = std::numeric_limits<int>::max();
    if (sampleCountTableDataSize > uint64_t(compressorMaxDataSize))
    {
        THROW (IEX_NAMESPACE::ArgExc, "This version of the library does not "
              << "support the allocation of data with size  > "
              << compressorMaxDataSize
              << " file table size    :" << sampleCountTableDataSize << ".\n");
    }
    streamData->is->read(data->sampleCountTableBuffer, static_cast<int>(sampleCountTableDataSize));

    const char* readPtr;


    if (sampleCountTableDataSize < static_cast<uint64_t>(data->maxSampleCountTableSize))
    {
        if(!data->sampleCountTableComp)
        {
            THROW(IEX_NAMESPACE::ArgExc,"Deep scanline data corrupt at chunk " << lineBlockId << " (sampleCountTableDataSize error)");
        }
        data->sampleCountTableComp->uncompress(data->sampleCountTableBuffer,
                                               static_cast<int>(sampleCountTableDataSize),
                                               minY,
                                               readPtr);
    }
    else readPtr = data->sampleCountTableBuffer;

    char* base = data->sampleCountSliceBase;
    int xStride = data->sampleCountXStride;
    int yStride = data->sampleCountYStride;


    size_t cumulative_total_samples=0;

    for (int y = minY; y <= maxY; y++)
    {
        int yInDataWindow = y - data->minY;
        data->lineSampleCount[yInDataWindow] = 0;

        int lastAccumulatedCount = 0;
        for (int x = data->minX; x <= data->maxX; x++)
        {
            int accumulatedCount, count;


            Xdr::read <CharPtrIO> (readPtr, accumulatedCount);


            if (accumulatedCount < lastAccumulatedCount)
            {
                THROW(IEX_NAMESPACE::ArgExc,"Deep scanline sampleCount data corrupt at chunk " << lineBlockId << " (negative sample count detected)");
            }

            count = accumulatedCount - lastAccumulatedCount;
            lastAccumulatedCount = accumulatedCount;


            data->sampleCount[yInDataWindow][x - data->minX] = count;
            data->lineSampleCount[yInDataWindow] += count;
            sampleCount(base, xStride, yStride, x, y) = count;
        }
        cumulative_total_samples+=data->lineSampleCount[yInDataWindow];
        if(cumulative_total_samples*data->combinedSampleSize > unpackedDataSize)
        {
            THROW(IEX_NAMESPACE::ArgExc,"Deep scanline sampleCount data corrupt at chunk " << lineBlockId << ": pixel data only contains " << unpackedDataSize
            << " bytes of data but table references at least " << cumulative_total_samples*data->combinedSampleSize << " bytes of sample data" );
        }
        data->gotSampleCount[y - data->minY] = true;
    }
}
