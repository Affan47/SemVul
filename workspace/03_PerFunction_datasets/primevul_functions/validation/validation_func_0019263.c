DwaCompressor::compress
    (const char             *inPtr,
     int                    inSize,
     IMATH_NAMESPACE::Box2i range,
     const char             *&outPtr)
{
    const char *inDataPtr   = inPtr;
    char       *packedAcEnd = 0;
    char       *packedDcEnd = 0;
    int         fileVersion = 2;


    if (fileVersion < 2)
        initializeLegacyChannelRules();
    else
        initializeDefaultChannelRules();

    size_t outBufferSize = 0;
    initializeBuffers(outBufferSize);

    unsigned short          channelRuleSize = 0;
    std::vector<Classifier> channelRules;
    if (fileVersion >= 2)
    {
        relevantChannelRules(channelRules);

        channelRuleSize = Xdr::size<unsigned short>();
        for (size_t i = 0; i < channelRules.size(); ++i)
            channelRuleSize += channelRules[i].size();
    }


    outBufferSize += channelRuleSize;
    if (outBufferSize > _outBufferSize)
    {
        _outBufferSize = outBufferSize;
        if (_outBuffer != 0)
            delete[] _outBuffer;
        _outBuffer = new char[outBufferSize];
    }

    char *outDataPtr = &_outBuffer[NUM_SIZES_SINGLE * sizeof(OPENEXR_IMF_NAMESPACE::Int64) +
                                   channelRuleSize];


    if (_packedAcBuffer)
        packedAcEnd = _packedAcBuffer;

    if (_packedDcBuffer)
        packedDcEnd = _packedDcBuffer;

    #define OBIDX(x) (Int64 *)&_outBuffer[x * sizeof (Int64)]

    Int64 *version                 = OBIDX (VERSION);
    Int64 *unknownUncompressedSize = OBIDX (UNKNOWN_UNCOMPRESSED_SIZE);
    Int64 *unknownCompressedSize   = OBIDX (UNKNOWN_COMPRESSED_SIZE);
    Int64 *acCompressedSize        = OBIDX (AC_COMPRESSED_SIZE);
    Int64 *dcCompressedSize        = OBIDX (DC_COMPRESSED_SIZE);
    Int64 *rleCompressedSize       = OBIDX (RLE_COMPRESSED_SIZE);
    Int64 *rleUncompressedSize     = OBIDX (RLE_UNCOMPRESSED_SIZE);
    Int64 *rleRawSize              = OBIDX (RLE_RAW_SIZE);

    Int64 *totalAcUncompressedCount = OBIDX (AC_UNCOMPRESSED_COUNT);
    Int64 *totalDcUncompressedCount = OBIDX (DC_UNCOMPRESSED_COUNT);

    Int64 *acCompression            = OBIDX (AC_COMPRESSION);

    int minX   = range.min.x;
    int maxX   = std::min(range.max.x, _max[0]);
    int minY   = range.min.y;
    int maxY   = std::min(range.max.y, _max[1]);


    memset (_outBuffer, 0, NUM_SIZES_SINGLE * sizeof (Int64));


    *version       = fileVersion;
    *acCompression = _acCompression;

    setupChannelData (minX, minY, maxX, maxY);

    if (fileVersion >= 2)
    {
        char *writePtr = &_outBuffer[NUM_SIZES_SINGLE * sizeof(OPENEXR_IMF_NAMESPACE::Int64)];
        Xdr::write<CharPtrIO> (writePtr, channelRuleSize);

        for (size_t i = 0; i < channelRules.size(); ++i)
            channelRules[i].write(writePtr);
    }


    std::vector<bool> encodedChannels (_channelData.size());
    std::vector< std::vector<const char *> > rowPtrs (_channelData.size());

    for (unsigned int chan = 0; chan < _channelData.size(); ++chan)
        encodedChannels[chan] = false;

    inDataPtr =  inPtr;

    for (int y = minY; y <= maxY; ++y)
    {
        for (unsigned int chan = 0; chan < _channelData.size(); ++chan)
        {

            ChannelData *cd = &_channelData[chan];

            if (IMATH_NAMESPACE::modp(y, cd->ySampling) != 0)
                continue;

            rowPtrs[chan].push_back(inDataPtr);
            inDataPtr += cd->width * OPENEXR_IMF_NAMESPACE::pixelTypeSize(cd->type);
        }
    }

    inDataPtr = inPtr;


    for (unsigned int csc = 0; csc < _cscSets.size(); ++csc)
    {

        LossyDctEncoderCsc encoder
            (_dwaCompressionLevel / 100000.f,
             rowPtrs[_cscSets[csc].idx[0]],
             rowPtrs[_cscSets[csc].idx[1]],
             rowPtrs[_cscSets[csc].idx[2]],
             packedAcEnd,
             packedDcEnd,
             dwaCompressorToNonlinear,
             _channelData[_cscSets[csc].idx[0]].width,
             _channelData[_cscSets[csc].idx[0]].height,
             _channelData[_cscSets[csc].idx[0]].type,
             _channelData[_cscSets[csc].idx[1]].type,
             _channelData[_cscSets[csc].idx[2]].type);

        encoder.execute();

        *totalAcUncompressedCount  += encoder.numAcValuesEncoded();
        *totalDcUncompressedCount  += encoder.numDcValuesEncoded();

        packedAcEnd += encoder.numAcValuesEncoded() * sizeof(unsigned short);
        packedDcEnd += encoder.numDcValuesEncoded() * sizeof(unsigned short);

        encodedChannels[_cscSets[csc].idx[0]] = true;
        encodedChannels[_cscSets[csc].idx[1]] = true;
        encodedChannels[_cscSets[csc].idx[2]] = true;
    }

    for (unsigned int chan = 0; chan < _channelData.size(); ++chan)
    {
        ChannelData *cd = &_channelData[chan];

        if (encodedChannels[chan])
            continue;

        switch (cd->compression)
        {
          case LOSSY_DCT:


            {
                const unsigned short *nonlinearLut = 0;

                if (!cd->pLinear)
                    nonlinearLut = dwaCompressorToNonlinear;

                LossyDctEncoder encoder
                    (_dwaCompressionLevel / 100000.f,
                     rowPtrs[chan],
                     packedAcEnd,
                     packedDcEnd,
                     nonlinearLut,
                     cd->width,
                     cd->height,
                     cd->type);

                encoder.execute();

                *totalAcUncompressedCount  += encoder.numAcValuesEncoded();
                *totalDcUncompressedCount  += encoder.numDcValuesEncoded();

                packedAcEnd +=
                    encoder.numAcValuesEncoded() * sizeof (unsigned short);

                packedDcEnd +=
                    encoder.numDcValuesEncoded() * sizeof (unsigned short);
            }

            break;

          case RLE:


            for (unsigned int y = 0; y < rowPtrs[chan].size(); ++y)
            {
                const char *row = rowPtrs[chan][y];

                for (int x = 0; x < cd->width; ++x)
                {
                    for (int byte = 0;
                         byte < OPENEXR_IMF_NAMESPACE::pixelTypeSize (cd->type);
                         ++byte)
                    {

                        *cd->planarUncRleEnd[byte]++ = *row++;
                    }
                }

                *rleRawSize += cd->width * OPENEXR_IMF_NAMESPACE::pixelTypeSize(cd->type);
            }

            break;

          case UNKNOWN:


            {
                int scanlineSize = cd->width * OPENEXR_IMF_NAMESPACE::pixelTypeSize(cd->type);

                for (unsigned int y = 0; y < rowPtrs[chan].size(); ++y)
                {
                    memcpy (cd->planarUncBufferEnd,
                            rowPtrs[chan][y],
                            scanlineSize);

                    cd->planarUncBufferEnd += scanlineSize;
                }

                *unknownUncompressedSize += cd->planarUncSize;
            }

            break;

          default:

            assert (false);
        }

        encodedChannels[chan] = true;
    }


    if (*unknownUncompressedSize > 0)
    {
        uLongf inSize  = (uLongf)(*unknownUncompressedSize);
        uLongf outSize = compressBound (inSize);

        if (Z_OK != ::compress2 ((Bytef *)outDataPtr,
                                 &outSize,
                                 (const Bytef *)_planarUncBuffer[UNKNOWN],
                                 inSize,
                                 9))
        {
            throw IEX_NAMESPACE::BaseExc ("Data compression (zlib) failed.");
        }

        outDataPtr += outSize;
        *unknownCompressedSize = outSize;
    }


    if (*totalAcUncompressedCount > 0)
    {
        switch (_acCompression)
        {
          case STATIC_HUFFMAN:

            *acCompressedSize = (int)
                hufCompress((unsigned short *)_packedAcBuffer,
                            (int)*totalAcUncompressedCount,
                            outDataPtr);
            break;

          case DEFLATE:

            {
                uLongf destLen = compressBound (
                    (*totalAcUncompressedCount) * sizeof (unsigned short));

                if (Z_OK != ::compress2
                                ((Bytef *)outDataPtr,
                                 &destLen,
                                 (Bytef *)_packedAcBuffer,
                                 (uLong)(*totalAcUncompressedCount
                                                * sizeof (unsigned short)),
                                 9))
                {
                    throw IEX_NAMESPACE::InputExc ("Data compression (zlib) failed.");
                }

                *acCompressedSize = destLen;
            }

            break;

          default:

            assert (false);
        }

        outDataPtr += *acCompressedSize;
    }


    if (*totalDcUncompressedCount > 0)
    {
        *dcCompressedSize = _zip->compress
            (_packedDcBuffer,
             (int)(*totalDcUncompressedCount) * sizeof (unsigned short),
             outDataPtr);

        outDataPtr += *dcCompressedSize;
    }


    if (*rleRawSize > 0)
    {
        *rleUncompressedSize = rleCompress
            ((int)(*rleRawSize),
             _planarUncBuffer[RLE],
             (signed char *)_rleBuffer);

        uLongf dstLen = compressBound ((uLongf)*rleUncompressedSize);

        if (Z_OK != ::compress2
                        ((Bytef *)outDataPtr,
                         &dstLen,
                         (Bytef *)_rleBuffer,
                         (uLong)(*rleUncompressedSize),
                         9))
        {
            throw IEX_NAMESPACE::BaseExc ("Error compressing RLE'd data.");
        }

       *rleCompressedSize = dstLen;
        outDataPtr       += *rleCompressedSize;
    }


    for (int i = 0; i < NUM_SIZES_SINGLE; ++i)
    {
        Int64  src = *(((Int64 *)_outBuffer) + i);
        char  *dst = (char *)(((Int64 *)_outBuffer) + i);

        Xdr::write<CharPtrIO> (dst, src);
    }


    outPtr = _outBuffer;

    return static_cast<int>(outDataPtr - _outBuffer + 1);
}
