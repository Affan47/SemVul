readPixelData (InputStreamMutex *streamData,
               ScanLineInputFile::Data *ifd,
	       int minY,
	       char *&buffer,
	       int &dataSize)
{


    int lineBufferNumber = (minY - ifd->minY) / ifd->linesInBuffer;
    if (lineBufferNumber < 0 || lineBufferNumber >= int(ifd->lineOffsets.size()))
        THROW (IEX_NAMESPACE::InputExc, "Invalid scan line " << minY << " requested or missing.");

    Int64 lineOffset = ifd->lineOffsets[lineBufferNumber];

    if (lineOffset == 0)
	THROW (IEX_NAMESPACE::InputExc, "Scan line " << minY << " is missing.");


    if ( !isMultiPart(ifd->version) )
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
    OPENEXR_IMF_INTERNAL_NAMESPACE::Xdr::read <OPENEXR_IMF_INTERNAL_NAMESPACE::StreamIO> (*streamData->is, dataSize);

    if (yInFile != minY)
        throw IEX_NAMESPACE::InputExc ("Unexpected data block y coordinate.");

    if (dataSize < 0 || dataSize > static_cast<int>(ifd->lineBufferSize) )
        throw IEX_NAMESPACE::InputExc ("Unexpected data block length.");


    if (streamData->is->isMemoryMapped ())
        buffer = streamData->is->readMemoryMapped (dataSize);
    else
        streamData->is->read (buffer, dataSize);


    if (ifd->lineOrder == INCREASING_Y)
        ifd->nextLineBufferMinY = minY + ifd->linesInBuffer;
    else
        ifd->nextLineBufferMinY = minY - ifd->linesInBuffer;
}
