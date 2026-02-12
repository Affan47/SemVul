readNextTileData (InputStreamMutex *streamData,
                  TiledInputFile::Data *ifd,
		  int &dx, int &dy,
		  int &lx, int &ly,
                  char * & buffer,
		  int &dataSize)
{


    if(isMultiPart(ifd->version))
    {
        int part;
        Xdr::read <StreamIO> (*streamData->is, part);
        if(part!=ifd->partNumber)
        {
           throw IEX_NAMESPACE::InputExc("Unexpected part number in readNextTileData");
        }
    }


    Xdr::read <StreamIO> (*streamData->is, dx);
    Xdr::read <StreamIO> (*streamData->is, dy);
    Xdr::read <StreamIO> (*streamData->is, lx);
    Xdr::read <StreamIO> (*streamData->is, ly);
    Xdr::read <StreamIO> (*streamData->is, dataSize);

    if (dataSize > (int) ifd->tileBufferSize)
        throw IEX_NAMESPACE::InputExc ("Unexpected tile block length.");


    streamData->is->read (buffer, dataSize);


    streamData->currentPosition += 5 * Xdr::size<int>() + dataSize;
}
