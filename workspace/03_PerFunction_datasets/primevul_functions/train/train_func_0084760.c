readPixelData (InputStreamMutex *streamData,
               DeepScanLineInputFile::Data *ifd,
               int minY,
               char *&buffer,
               uint64_t &packedDataSize,
               uint64_t &unpackedDataSize)
{


    int lineBufferNumber = (minY - ifd->minY) / ifd->linesInBuffer;

    uint64_t lineOffset = ifd->lineOffsets[lineBufferNumber];

    if (lineOffset == 0)
        THROW (IEX_NAMESPACE::InputExc, "Scan line " << minY << " is missing.");


    if (!isMultiPart(ifd->version))
    {
        if (ifd->nextLineBufferMinY != minY)
            streamData->is->seekg (lineOffset);
    }
    else
    {


        if (streamData->is->tellg() != ifd->lineOffsets[lineBufferNumber])
            streamData->is->seekg (lineOffset);
    }


    int yInFile;


    if (isMultiPart(ifd->version))
    {
        int partNumber;
        OPENEXR_IMF_INTERNAL_NAMESPACE::Xdr::read <OPENEXR_IMF_INTERNAL_NAMESPACE::StreamIO> (*streamData->is, partNumber);
        if (partNumber != ifd->partNumber)
        {
            THROW (IEX_NAMESPACE::ArgExc, "Unexpected part number " << partNumber
                   << ", should be " << ifd->partNumber << ".");
        }
    }

    OPENEXR_IMF_INTERNAL_NAMESPACE::Xdr::read <OPENEXR_IMF_INTERNAL_NAMESPACE::StreamIO> (*streamData->is, yInFile);

    if (yInFile != minY)
        throw IEX_NAMESPACE::InputExc ("Unexpected data block y coordinate.");

    uint64_t sampleCountTableSize;
    OPENEXR_IMF_INTERNAL_NAMESPACE::Xdr::read <OPENEXR_IMF_INTERNAL_NAMESPACE::StreamIO> (*streamData->is, sampleCountTableSize);
    OPENEXR_IMF_INTERNAL_NAMESPACE::Xdr::read <OPENEXR_IMF_INTERNAL_NAMESPACE::StreamIO> (*streamData->is, packedDataSize);
    OPENEXR_IMF_INTERNAL_NAMESPACE::Xdr::read <OPENEXR_IMF_INTERNAL_NAMESPACE::StreamIO> (*streamData->is, unpackedDataSize);


    int compressorMaxDataSize = std::numeric_limits<int>::max();
    if (packedDataSize   > uint64_t(compressorMaxDataSize) ||
        unpackedDataSize > uint64_t(compressorMaxDataSize))
    {
        THROW (IEX_NAMESPACE::ArgExc, "This version of the library does not support "
              << "the allocation of data with size  > " << compressorMaxDataSize
              << " file unpacked size :" << unpackedDataSize
              << " file packed size   :" << packedDataSize << ".\n");
    }


    Xdr::skip <StreamIO> (*streamData->is, static_cast<int>(sampleCountTableSize));


    if (streamData->is->isMemoryMapped ())
        buffer = streamData->is->readMemoryMapped (static_cast<int>(packedDataSize));
    else
    {


        if (buffer != 0) delete[] buffer;
        buffer = new char[packedDataSize];
        streamData->is->read (buffer, static_cast<int>(packedDataSize));
    }


    if (ifd->lineOrder == INCREASING_Y)
        ifd->nextLineBufferMinY = minY + ifd->linesInBuffer;
    else
        ifd->nextLineBufferMinY = minY - ifd->linesInBuffer;
}
