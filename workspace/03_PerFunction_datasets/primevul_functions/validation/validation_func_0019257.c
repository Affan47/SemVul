DwaCompressor::initializeBuffers (size_t &outBufferSize)
{
    classifyChannels (_channels, _channelData, _cscSets);


    int maxOutBufferSize  = 0;
    int numLossyDctChans  = 0;
    int unknownBufferSize = 0;
    int rleBufferSize     = 0;

    int maxLossyDctAcSize = (int)ceil ((float)numScanLines() / 8.0f) *
                            (int)ceil ((float)(_max[0] - _min[0] + 1) / 8.0f) *
                            63 * sizeof (unsigned short);

    int maxLossyDctDcSize = (int)ceil ((float)numScanLines() / 8.0f) *
                            (int)ceil ((float)(_max[0] - _min[0] + 1) / 8.0f) *
                            sizeof (unsigned short);

    for (unsigned int chan = 0; chan < _channelData.size(); ++chan)
    {
        switch (_channelData[chan].compression)
        {
          case LOSSY_DCT:


            maxOutBufferSize += std::max(
                            (int)(2 * maxLossyDctAcSize + 65536),
                            (int)compressBound (maxLossyDctAcSize) );
            numLossyDctChans++;
            break;

          case RLE:
            {


                int rleAmount = 2 * numScanLines() * (_max[0] - _min[0] + 1) *
                                OPENEXR_IMF_NAMESPACE::pixelTypeSize (_channelData[chan].type);

                rleBufferSize += rleAmount;
            }
            break;


          case UNKNOWN:

            unknownBufferSize += numScanLines() * (_max[0] - _min[0] + 1) *
                                 OPENEXR_IMF_NAMESPACE::pixelTypeSize (_channelData[chan].type);
            break;

          default:

            throw IEX_NAMESPACE::NoImplExc ("Unhandled compression scheme case");
            break;
        }
    }


    maxOutBufferSize += (int)compressBound ((uLongf)rleBufferSize);


    maxOutBufferSize += (int)compressBound ((uLongf)unknownBufferSize);


    if (_zip == 0)
        _zip = new Zip (maxLossyDctDcSize * numLossyDctChans);
    else if (_zip->maxRawSize() < static_cast<size_t>(maxLossyDctDcSize * numLossyDctChans))
    {
        delete _zip;
        _zip = new Zip (maxLossyDctDcSize * numLossyDctChans);
    }


    maxOutBufferSize += _zip->maxCompressedSize();


    maxOutBufferSize += NUM_SIZES_SINGLE * sizeof (Int64);


    outBufferSize = maxOutBufferSize;


    if (static_cast<size_t>(maxLossyDctAcSize * numLossyDctChans) > _packedAcBufferSize)
    {
        _packedAcBufferSize = maxLossyDctAcSize * numLossyDctChans;
        if (_packedAcBuffer != 0)
            delete[] _packedAcBuffer;
        _packedAcBuffer = new char[_packedAcBufferSize];
    }


    if (static_cast<size_t>(maxLossyDctDcSize * numLossyDctChans) > _packedDcBufferSize)
    {
        _packedDcBufferSize = maxLossyDctDcSize * numLossyDctChans;
        if (_packedDcBuffer != 0)
            delete[] _packedDcBuffer;
        _packedDcBuffer     = new char[_packedDcBufferSize];
    }

    if (static_cast<size_t>(rleBufferSize) > _rleBufferSize)
    {
        _rleBufferSize = rleBufferSize;
        if (_rleBuffer != 0)
            delete[] _rleBuffer;
        _rleBuffer = new char[rleBufferSize];
    }


    int planarUncBufferSize[NUM_COMPRESSOR_SCHEMES];
    for (int i=0; i<NUM_COMPRESSOR_SCHEMES; ++i)
        planarUncBufferSize[i] = 0;

    for (unsigned int chan = 0; chan < _channelData.size(); ++chan)
    {
        switch (_channelData[chan].compression)
        {
          case LOSSY_DCT:
            break;

          case RLE:
            planarUncBufferSize[RLE] +=
                     numScanLines() * (_max[0] - _min[0] + 1) *
                     OPENEXR_IMF_NAMESPACE::pixelTypeSize (_channelData[chan].type);
            break;

          case UNKNOWN:
            planarUncBufferSize[UNKNOWN] +=
                     numScanLines() * (_max[0] - _min[0] + 1) *
                     OPENEXR_IMF_NAMESPACE::pixelTypeSize (_channelData[chan].type);
            break;

          default:
            throw IEX_NAMESPACE::NoImplExc ("Unhandled compression scheme case");
            break;
        }
    }


    if (planarUncBufferSize[UNKNOWN] > 0)
    {
        planarUncBufferSize[UNKNOWN] =
            compressBound ((uLongf)planarUncBufferSize[UNKNOWN]);
    }

    for (int i = 0; i < NUM_COMPRESSOR_SCHEMES; ++i)
    {
        if (static_cast<size_t>(planarUncBufferSize[i]) > _planarUncBufferSize[i])
        {
            _planarUncBufferSize[i] = planarUncBufferSize[i];
            if (_planarUncBuffer[i] != 0)
                delete[] _planarUncBuffer[i];
            _planarUncBuffer[i] = new char[planarUncBufferSize[i]];
        }
    }
}
