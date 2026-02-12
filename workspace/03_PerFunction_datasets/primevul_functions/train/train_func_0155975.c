bytesPerDeepLineTable (const Header &header,
                       int minY, int maxY,
                       const char* base,
                       int xStride,
                       int yStride,
                       vector<size_t> &bytesPerLine)
{
    const Box2i &dataWindow = header.dataWindow();
    const ChannelList &channels = header.channels();

    for (ChannelList::ConstIterator c = channels.begin();
         c != channels.end();
         ++c)
    {
        const int ySampling = abs(c.channel().ySampling);
        const int xSampling = abs(c.channel().xSampling);
        const uint64_t pixelSize = pixelTypeSize (c.channel().type);


        const int sampleMinY = roundToNextMultiple(minY, ySampling);
        const int sampleMaxY = roundToPrevMultiple(maxY, ySampling);
        const int sampleMinX = roundToNextMultiple(dataWindow.min.x, xSampling);
        const int sampleMaxX = roundToPrevMultiple(dataWindow.max.x, xSampling);

        for (int y = sampleMinY; y <= sampleMaxY; y+=ySampling)
        {
            uint64_t nBytes = 0;
            for (int x = sampleMinX; x <= sampleMaxX; x += xSampling)
            {
                nBytes += pixelSize *
                          static_cast<uint64_t>(sampleCount(base, xStride, yStride, x, y));
            }


            if( static_cast<uint64_t>(bytesPerLine[y - dataWindow.min.y]) + nBytes > SIZE_MAX)
            {
                throw IEX_NAMESPACE::IoExc("Scanline size too large");
            }

            bytesPerLine[y - dataWindow.min.y] += nBytes;
        }
    }

    size_t maxBytesPerLine = 0;

    for (int y = minY; y <= maxY; ++y)
    {
        if (maxBytesPerLine < bytesPerLine[y - dataWindow.min.y])
        {
            maxBytesPerLine = bytesPerLine[y - dataWindow.min.y];
        }
    }

    return maxBytesPerLine;
}
