LineBufferTask::execute ()
{
    try
    {


        if (_lineBuffer->uncompressedData == 0)
        {
            uint64_t uncompressedSize = 0;
            int maxY = min (_lineBuffer->maxY, _ifd->maxY);

            for (int i = _lineBuffer->minY - _ifd->minY;
                 i <= maxY - _ifd->minY;
                 ++i)
            {
                uncompressedSize += (int) _ifd->bytesPerLine[i];
            }


            if (_lineBuffer->compressor != 0)
                delete _lineBuffer->compressor;
            uint64_t maxBytesPerLine = 0;
            for (int i = _lineBuffer->minY - _ifd->minY;
                 i <= maxY - _ifd->minY;
                 ++i)
            {
                if (_ifd->bytesPerLine[i] > maxBytesPerLine)
                    maxBytesPerLine = _ifd->bytesPerLine[i];
            }
            _lineBuffer->compressor = newCompressor(_ifd->header.compression(),
                                                    maxBytesPerLine,
                                                    _ifd->header);

            if (_lineBuffer->compressor &&
                _lineBuffer->packedDataSize < uncompressedSize)
            {
                _lineBuffer->format = _lineBuffer->compressor->format();

                _lineBuffer->packedDataSize = _lineBuffer->compressor->uncompress
                    (_lineBuffer->buffer, static_cast<int>(_lineBuffer->packedDataSize),
                     _lineBuffer->minY, _lineBuffer->uncompressedData);
            }
            else
            {


                _lineBuffer->format = Compressor::XDR;
                _lineBuffer->uncompressedData = _lineBuffer->buffer;

                if(_lineBuffer->packedDataSize!=maxBytesPerLine)
                {
                    THROW (IEX_NAMESPACE::InputExc, "Incorrect size for uncompressed data. Expected " << maxBytesPerLine << " got " << _lineBuffer->packedDataSize << " bytes");
                }
            }
        }

        int yStart, yStop, dy;

        if (_ifd->lineOrder == INCREASING_Y)
        {
            yStart = _scanLineMin;
            yStop = _scanLineMax + 1;
            dy = 1;
        }
        else
        {
            yStart = _scanLineMax;
            yStop = _scanLineMin - 1;
            dy = -1;
        }

        for (int y = yStart; y != yStop; y += dy)
        {


            const char *readPtr = _lineBuffer->uncompressedData +
                                  _ifd->offsetInLineBuffer[y - _ifd->minY];


            for (unsigned int i = 0; i < _ifd->slices.size(); ++i)
            {


                InSliceInfo &slice = *_ifd->slices[i];

                if (modp (y, slice.ySampling) != 0)
                    continue;


                if (slice.skip)
                {


                    skipChannel (readPtr, slice.typeInFile,
                                 _ifd->lineSampleCount[y - _ifd->minY]);
                }
                else
                {


                    int width = (_ifd->maxX - _ifd->minX + 1);

                    ptrdiff_t base = reinterpret_cast<ptrdiff_t>(&_ifd->sampleCount[0][0]);
                    base -= sizeof(unsigned int)*_ifd->minX;
                    base -= sizeof(unsigned int)*static_cast<ptrdiff_t>(_ifd->minY) * static_cast<ptrdiff_t>(width);

                    copyIntoDeepFrameBuffer (readPtr, slice.base,
                                             reinterpret_cast<char*>(base),
                                             sizeof(unsigned int) * 1,
                                             sizeof(unsigned int) * width,
                                             y, _ifd->minX, _ifd->maxX,
                                             0, 0,
                                             0, 0,
                                             slice.sampleStride,
                                             slice.xPointerStride,
                                             slice.yPointerStride,
                                             slice.fill,
                                             slice.fillValue, _lineBuffer->format,
                                             slice.typeInFrameBuffer,
                                             slice.typeInFile);
                }
            }
        }
    }
    catch (std::exception &e)
    {
        if (!_lineBuffer->hasException)
        {
            _lineBuffer->exception = e.what();
            _lineBuffer->hasException = true;
        }
    }
    catch (...)
    {
        if (!_lineBuffer->hasException)
        {
            _lineBuffer->exception = "unrecognized exception";
            _lineBuffer->hasException = true;
        }
    }
}
