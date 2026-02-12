TileBufferTask::execute ()
{
    try
    {


        Box2i tileRange =  OPENEXR_IMF_INTERNAL_NAMESPACE::dataWindowForTile (
                _ifd->tileDesc,
                _ifd->minX, _ifd->maxX,
                _ifd->minY, _ifd->maxY,
                _tileBuffer->dx,
                _tileBuffer->dy,
                _tileBuffer->lx,
                _tileBuffer->ly);

        int numPixelsPerScanLine = tileRange.max.x - tileRange.min.x + 1;

        int numPixelsInTile = numPixelsPerScanLine *
                            (tileRange.max.y - tileRange.min.y + 1);

        int sizeOfTile = _ifd->bytesPerPixel * numPixelsInTile;


        if (_tileBuffer->compressor && _tileBuffer->dataSize < sizeOfTile)
        {
            _tileBuffer->format = _tileBuffer->compressor->format();

            _tileBuffer->dataSize = _tileBuffer->compressor->uncompressTile
		(_tileBuffer->buffer, _tileBuffer->dataSize,
		 tileRange, _tileBuffer->uncompressedData);
        }
        else
        {


            _tileBuffer->format = Compressor::XDR;
            _tileBuffer->uncompressedData = _tileBuffer->buffer;
        }


        const char *readPtr = _tileBuffer->uncompressedData;


        for (int y = tileRange.min.y; y <= tileRange.max.y; ++y)
        {


            for (unsigned int i = 0; i < _ifd->slices.size(); ++i)
            {
                const TInSliceInfo &slice = _ifd->slices[i];


                int xOffset = slice.xTileCoords * tileRange.min.x;
                int yOffset = slice.yTileCoords * tileRange.min.y;


                if (slice.skip)
                {


                    skipChannel (readPtr, slice.typeInFile,
                                 numPixelsPerScanLine);
                }
                else
                {


                    char *writePtr = slice.base +
                                     (y - yOffset) * slice.yStride +
                                     (tileRange.min.x - xOffset) *
                                     slice.xStride;

                    char *endPtr = writePtr +
                                   (numPixelsPerScanLine - 1) * slice.xStride;

                    copyIntoFrameBuffer (readPtr, writePtr, endPtr,
                                         slice.xStride,
                                         slice.fill, slice.fillValue,
                                         _tileBuffer->format,
                                         slice.typeInFrameBuffer,
                                         slice.typeInFile);
                }
            }
        }
    }
    catch (std::exception &e)
    {
        if (!_tileBuffer->hasException)
        {
            _tileBuffer->exception = e.what ();
            _tileBuffer->hasException = true;
        }
    }
    catch (...)
    {
        if (!_tileBuffer->hasException)
        {
            _tileBuffer->exception = "unrecognized exception";
            _tileBuffer->hasException = true;
        }
    }
}
