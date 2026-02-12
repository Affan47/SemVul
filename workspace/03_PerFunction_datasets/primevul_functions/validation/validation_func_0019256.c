DwaCompressor::LossyDctEncoderBase::execute ()
{
    int  numBlocksX   = (int)ceil ((float)_width / 8.0f);
    int  numBlocksY   = (int)ceil ((float)_height/ 8.0f);

    half halfZigCoef[64];
    half halfCoef[64];

    std::vector<unsigned short *> currDcComp (_rowPtrs.size());
    unsigned short               *currAcComp = (unsigned short *)_packedAc;

    _dctData.resize (_rowPtrs.size());
    _numAcComp = 0;
    _numDcComp = 0;

    assert (_type.size() == _rowPtrs.size());
    assert ((_rowPtrs.size() == 3) || (_rowPtrs.size() == 1));


    int tmpHalfBufferElements = 0;

    for (unsigned int chan = 0; chan < _rowPtrs.size(); ++chan)
        if (_type[chan] == FLOAT)
            tmpHalfBufferElements += _width * _height;

    std::vector<unsigned short> tmpHalfBuffer (tmpHalfBufferElements);

    char *tmpHalfBufferPtr = 0;

    if (tmpHalfBufferElements)
        tmpHalfBufferPtr = (char *)&tmpHalfBuffer[0];


    for (unsigned int chan = 0; chan < _rowPtrs.size(); ++chan)
    {
        if (_type[chan] != FLOAT)
            continue;

        for (int y = 0; y < _height; ++y)
        {
            float       src = 0;
            const char *srcXdr = _rowPtrs[chan][y];
            char       *dstXdr = tmpHalfBufferPtr;

            for (int x = 0; x < _width; ++x)
            {

                Xdr::read<CharPtrIO> (srcXdr, src);


                src = std::max (
                    std::min ((float) std::numeric_limits<half>::max(), src),
                              (float)-std::numeric_limits<half>::max());

                Xdr::write<CharPtrIO> (dstXdr, ((half)src).bits());


            }

            _rowPtrs[chan][y] = (const char *)tmpHalfBufferPtr;
            tmpHalfBufferPtr += _width * sizeof (unsigned short);
        }
    }


    currDcComp[0] = (unsigned short *)_packedDc;

    for (unsigned int chan = 1; chan < _rowPtrs.size(); ++chan)
        currDcComp[chan] = currDcComp[chan-1] + numBlocksX * numBlocksY;

    for (int blocky = 0; blocky < numBlocksY; ++blocky)
    {
        for (int blockx = 0; blockx < numBlocksX; ++blockx)
        {
            half           h;
            unsigned short tmpShortXdr, tmpShortNative;
            char          *tmpCharPtr;

            for (unsigned int chan = 0; chan < _rowPtrs.size(); ++chan)
            {


                for (int y = 0; y < 8; ++y)
                {
                    for (int x = 0; x < 8; ++x)
                    {
                        int vx = 8 * blockx + x;
                        int vy = 8 * blocky + y;

                        if (vx >= _width)
                            vx = _width - (vx - (_width - 1));

                        if (vx < 0) vx = _width-1;

                        if (vy >=_height)
                            vy = _height - (vy - (_height - 1));

                        if (vy < 0) vy = _height-1;

                        tmpShortXdr =
                            ((const unsigned short *)(_rowPtrs[chan])[vy])[vx];

                        if (_toNonlinear)
                        {
                            h.setBits (_toNonlinear[tmpShortXdr]);
                        }
                        else
                        {
                            const char *tmpConstCharPtr =
                                (const char *)(&tmpShortXdr);

                            Xdr::read<CharPtrIO>
                                (tmpConstCharPtr, tmpShortNative);

                            h.setBits(tmpShortNative);
                        }

                        _dctData[chan]._buffer[y * 8 + x] = (float)h;
                    }
                }
            }


            if (_rowPtrs.size() == 3)
            {
                csc709Forward64 (_dctData[0]._buffer,
                                 _dctData[1]._buffer,
                                 _dctData[2]._buffer);
            }

            for (unsigned int chan = 0; chan < _rowPtrs.size(); ++chan)
            {


                dctForward8x8(_dctData[chan]._buffer);


                if (chan == 0)
                {
                    for (int i = 0; i < 64; ++i)
                    {
                        halfCoef[i] =
                            quantize ((half)_dctData[chan]._buffer[i],
                                      _quantBaseError*_quantTableY[i]);
                    }
                }
                else
                {
                    for (int i = 0; i < 64; ++i)
                    {
                        halfCoef[i] =
                            quantize ((half)_dctData[chan]._buffer[i],
                                      _quantBaseError*_quantTableCbCr[i]);
                    }
                }

                toZigZag (halfZigCoef, halfCoef);


                for (int i = 0; i < 64; ++i)
                {
                    tmpCharPtr = (char *)&tmpShortXdr;
                    Xdr::write<CharPtrIO>(tmpCharPtr, halfZigCoef[i].bits());
                    halfZigCoef[i].setBits(tmpShortXdr);
                }


                *currDcComp[chan]++ = halfZigCoef[0].bits();
                _numDcComp++;


                rleAc (halfZigCoef, currAcComp);
            }
        }
    }
}
