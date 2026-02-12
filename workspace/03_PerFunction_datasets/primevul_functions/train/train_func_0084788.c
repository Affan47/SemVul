void DeepScanLineInputFile::readPixels (const char* rawPixelData,
                                        const DeepFrameBuffer& frameBuffer,
                                        int scanLine1,
                                        int scanLine2) const
{


    int data_scanline = *(int *) rawPixelData;
    uint64_t sampleCountTableDataSize=*(uint64_t *) (rawPixelData+4);
    uint64_t packedDataSize = *(uint64_t *) (rawPixelData+12);
    uint64_t unpackedDataSize = *(uint64_t *) (rawPixelData+20);


    Compressor * decomp = NULL;
    const char * uncompressed_data;
    Compressor::Format format = Compressor::XDR;
    if(packedDataSize <unpackedDataSize)
    {
        decomp = newCompressor(_data->header.compression(),
                                             unpackedDataSize,
                                             _data->header);

        decomp->uncompress(rawPixelData+28+sampleCountTableDataSize,
                           static_cast<int>(packedDataSize),
                           data_scanline, uncompressed_data);
        format = decomp->format();
    }
    else
    {


        format = Compressor::XDR;
        uncompressed_data = rawPixelData+28+sampleCountTableDataSize;
    }


    int yStart, yStop, dy;

    if (_data->lineOrder == INCREASING_Y)
    {
        yStart = scanLine1;
        yStop = scanLine2 + 1;
        dy = 1;
    }
    else
    {
        yStart = scanLine2;
        yStop = scanLine1 - 1;
        dy = -1;
    }


    const char* samplecount_base = frameBuffer.getSampleCountSlice().base;
    int samplecount_xstride = static_cast<int>(frameBuffer.getSampleCountSlice().xStride);
    int samplecount_ystride = static_cast<int>(frameBuffer.getSampleCountSlice().yStride);


    int minYInLineBuffer = data_scanline;
    int maxYInLineBuffer = min(minYInLineBuffer + _data->linesInBuffer - 1, _data->maxY);

    vector<size_t> bytesPerLine(1+_data->maxY-_data->minY);


    bytesPerDeepLineTable (_data->header,
                           minYInLineBuffer,
                           maxYInLineBuffer,
                           samplecount_base,
                           samplecount_xstride,
                           samplecount_ystride,
                           bytesPerLine);


    vector<size_t> offsetInLineBuffer;
    offsetInLineBufferTable (bytesPerLine,
                             minYInLineBuffer - _data->minY,
                             maxYInLineBuffer - _data->minY,
                             _data->linesInBuffer,
                             offsetInLineBuffer);


    const ChannelList & channels=header().channels();


    for (int y = yStart; y != yStop; y += dy)
    {

        const char *readPtr =uncompressed_data +
        offsetInLineBuffer[y - _data->minY];


        int lineSampleCount = -1;


        ChannelList::ConstIterator i = channels.begin();

        for (DeepFrameBuffer::ConstIterator j = frameBuffer.begin();
                                            j != frameBuffer.end();
             ++j)
        {
            while (i != channels.end() && strcmp (i.name(), j.name()) < 0)
            {


                if(lineSampleCount==-1)
                {
                     lineSampleCount=0;
                     const char * ptr = (samplecount_base+y*samplecount_ystride + samplecount_xstride*_data->minX);
                     for(int x=_data->minX;x<=_data->maxX;x++)
                     {

                          lineSampleCount+=*(const unsigned int *) ptr;
                          ptr+=samplecount_xstride;
                     }
                }

               skipChannel (readPtr, i.channel().type, lineSampleCount );

                ++i;
            }

            bool fill = false;

            if (i == channels.end() || strcmp (i.name(), j.name()) > 0)
            {


               fill = true;
            }
            if (modp (y, i.channel().ySampling) == 0)
            {

                copyIntoDeepFrameBuffer (readPtr, j.slice().base,
                                         samplecount_base,
                                         samplecount_xstride,
                                         samplecount_ystride,
                                         y, _data->minX, _data->maxX,
                                         0, 0,
                                         0, 0,
                                         j.slice().sampleStride,
                                         j.slice().xStride,
                                         j.slice().yStride,
                                         fill,
                                         j.slice().fillValue,
                                         format,
                                         j.slice().type,
                                         i.channel().type);

                ++i;

            }
        }
    }


    delete decomp;
}
