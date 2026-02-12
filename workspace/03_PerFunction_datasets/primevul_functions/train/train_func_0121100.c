readTileData (InputStreamMutex *streamData,
              TiledInputFile::Data *ifd,
	      int dx, int dy,
	      int lx, int ly,
              char *&buffer,
              int &dataSize)
{


    Int64 tileOffset = ifd->tileOffsets (dx, dy, lx, ly);

    if (tileOffset == 0)
    {
        THROW (IEX_NAMESPACE::InputExc, "Tile (" << dx << ", " << dy << ", " <<
			      lx << ", " << ly << ") is missing.");
    }


    if (!isMultiPart(ifd->version))
    {
        if (streamData->currentPosition != tileOffset)
            streamData->is->seekg (tileOffset);
    }
    else
    {


        if (streamData->is->tellg() != tileOffset)
            streamData->is->seekg (tileOffset);
    }


    int tileXCoord, tileYCoord, levelX, levelY;

    if (isMultiPart(ifd->version))
    {
        int partNumber;
        Xdr::read <StreamIO> (*streamData->is, partNumber);
        if (partNumber != ifd->partNumber)
        {
            THROW (IEX_NAMESPACE::ArgExc, "Unexpected part number " << partNumber
                   << ", should be " << ifd->partNumber << ".");
        }
    }

    OPENEXR_IMF_INTERNAL_NAMESPACE::Xdr::read <OPENEXR_IMF_INTERNAL_NAMESPACE::StreamIO> (*streamData->is, tileXCoord);
    OPENEXR_IMF_INTERNAL_NAMESPACE::Xdr::read <OPENEXR_IMF_INTERNAL_NAMESPACE::StreamIO> (*streamData->is, tileYCoord);
    OPENEXR_IMF_INTERNAL_NAMESPACE::Xdr::read <OPENEXR_IMF_INTERNAL_NAMESPACE::StreamIO> (*streamData->is, levelX);
    OPENEXR_IMF_INTERNAL_NAMESPACE::Xdr::read <OPENEXR_IMF_INTERNAL_NAMESPACE::StreamIO> (*streamData->is, levelY);
    OPENEXR_IMF_INTERNAL_NAMESPACE::Xdr::read <OPENEXR_IMF_INTERNAL_NAMESPACE::StreamIO> (*streamData->is, dataSize);

    if (tileXCoord != dx)
        throw IEX_NAMESPACE::InputExc ("Unexpected tile x coordinate.");

    if (tileYCoord != dy)
        throw IEX_NAMESPACE::InputExc ("Unexpected tile y coordinate.");

    if (levelX != lx)
        throw IEX_NAMESPACE::InputExc ("Unexpected tile x level number coordinate.");

    if (levelY != ly)
        throw IEX_NAMESPACE::InputExc ("Unexpected tile y level number coordinate.");

    if (dataSize < 0 || dataSize > static_cast<int>(ifd->tileBufferSize) )
        throw IEX_NAMESPACE::InputExc ("Unexpected tile block length.");


    if (streamData->is->isMemoryMapped ())
        buffer = streamData->is->readMemoryMapped (dataSize);
    else
        streamData->is->read (buffer, dataSize);


    streamData->currentPosition = tileOffset + 5 * Xdr::size<int>() + dataSize;
}
