DwaCompressor::LossyDctDecoderBase::execute ()
{
    size_t numComp        = _rowPtrs.size();
    int lastNonZero    = 0;
    int numBlocksX     = (int) ceil ((float)_width  / 8.0f);
    int numBlocksY     = (int) ceil ((float)_height / 8.0f);
    int leftoverX      = _width  - (numBlocksX-1) * 8;
    int leftoverY      = _height - (numBlocksY-1) * 8;

    int numFullBlocksX = (int)floor ((float)_width / 8.0f);

    unsigned short tmpShortNative = 0;
    unsigned short tmpShortXdr    = 0;
    const char *tmpConstCharPtr   = 0;

    unsigned short                    *currAcComp = (unsigned short *)_packedAc;
    std::vector<unsigned short *>      currDcComp (_rowPtrs.size());
    std::vector<SimdAlignedBuffer64us> halfZigBlock (_rowPtrs.size());

    if (_type.size() != _rowPtrs.size())
        throw IEX_NAMESPACE::BaseExc ("Row pointers and types mismatch in count");

    if ((_rowPtrs.size() != 3) && (_rowPtrs.size() != 1))
        throw IEX_NAMESPACE::NoImplExc ("Only 1 and 3 channel encoding is supported");

    _dctData.resize(numComp);


    unsigned char *rowBlockHandle = new unsigned char
        [numComp * numBlocksX * 64 * sizeof(unsigned short) + _SSE_ALIGNMENT];

    unsigned short *rowBlock[3];

    rowBlock[0] = (unsigned short*)rowBlockHandle;

    for (int i = 0; i < _SSE_ALIGNMENT; ++i)
    {
        if ((reinterpret_cast<uintptr_t>(rowBlockHandle + i) & _SSE_ALIGNMENT_MASK) == 0)
            rowBlock[0] = (unsigned short *)(rowBlockHandle + i);
    }

    for (size_t comp = 1; comp < numComp; ++comp)
        rowBlock[comp] = rowBlock[comp - 1] + numBlocksX * 64;


    currDcComp[0] = (unsigned short *)_packedDc;

    for (size_t comp = 1; comp < numComp; ++comp)
        currDcComp[comp] = currDcComp[comp - 1] + numBlocksX * numBlocksY;

    for (int blocky = 0; blocky < numBlocksY; ++blocky)
    {
        int maxY = 8;

        if (blocky == numBlocksY-1)
            maxY = leftoverY;

        int maxX = 8;

        for (int blockx = 0; blockx < numBlocksX; ++blockx)
        {
            if (blockx == numBlocksX-1)
                maxX = leftoverX;


            bool blockIsConstant = true;

            for (size_t comp = 0; comp < numComp; ++comp)
            {


                #ifdef IMF_HAVE_SSE2
                    {
                        __m128i *dst = (__m128i*)halfZigBlock[comp]._buffer;

                        dst[7] = _mm_setzero_si128();
                        dst[6] = _mm_setzero_si128();
                        dst[5] = _mm_setzero_si128();
                        dst[4] = _mm_setzero_si128();
                        dst[3] = _mm_setzero_si128();
                        dst[2] = _mm_setzero_si128();
                        dst[1] = _mm_setzero_si128();
                        dst[0] = _mm_insert_epi16
                            (_mm_setzero_si128(), *currDcComp[comp]++, 0);
                    }
                #else

                    memset (halfZigBlock[comp]._buffer, 0, 64 * 2);
                    halfZigBlock[comp]._buffer[0] = *currDcComp[comp]++;

                #endif

                _packedDcCount++;


                lastNonZero = unRleAc (currAcComp, halfZigBlock[comp]._buffer);


                if (!_isNativeXdr)
                {
                    for (int i = 0; i < 64; ++i)
                    {
                        tmpShortXdr      = halfZigBlock[comp]._buffer[i];
                        tmpConstCharPtr  = (const char *)&tmpShortXdr;

                        Xdr::read<CharPtrIO> (tmpConstCharPtr, tmpShortNative);

                        halfZigBlock[comp]._buffer[i] = tmpShortNative;
                    }
                }

                if (lastNonZero == 0)
                {


                    half h;

                    h.setBits (halfZigBlock[comp]._buffer[0]);
                    _dctData[comp]._buffer[0] = (float)h;

                    dctInverse8x8DcOnly (_dctData[comp]._buffer);
                }
                else
                {


                    blockIsConstant = false;


                    (*fromHalfZigZag)
                        (halfZigBlock[comp]._buffer, _dctData[comp]._buffer);


                    if (lastNonZero < 2)
                        dctInverse8x8_7(_dctData[comp]._buffer);
                    else if (lastNonZero < 3)
                        dctInverse8x8_6(_dctData[comp]._buffer);
                    else if (lastNonZero < 9)
                        dctInverse8x8_5(_dctData[comp]._buffer);
                    else if (lastNonZero < 10)
                        dctInverse8x8_4(_dctData[comp]._buffer);
                    else if (lastNonZero < 20)
                        dctInverse8x8_3(_dctData[comp]._buffer);
                    else if (lastNonZero < 21)
                        dctInverse8x8_2(_dctData[comp]._buffer);
                    else if (lastNonZero < 35)
                        dctInverse8x8_1(_dctData[comp]._buffer);
                    else
                        dctInverse8x8_0(_dctData[comp]._buffer);
                }
            }


            if (numComp == 3)
            {
                if (!blockIsConstant)
                {
                    csc709Inverse64 (_dctData[0]._buffer,
                                     _dctData[1]._buffer,
                                     _dctData[2]._buffer);

                }
                else
                {
                    csc709Inverse (_dctData[0]._buffer[0],
                                   _dctData[1]._buffer[0],
                                   _dctData[2]._buffer[0]);
                }
            }


            for (size_t comp = 0; comp < numComp; ++comp)
            {
                if (!blockIsConstant)
                {
                    (*convertFloatToHalf64)
                        (&rowBlock[comp][blockx*64], _dctData[comp]._buffer);
                }
                else
                {
                    #ifdef IMF_HAVE_SSE2

                        __m128i *dst = (__m128i*)&rowBlock[comp][blockx*64];

                        dst[0] = _mm_set1_epi16
                            (((half)_dctData[comp]._buffer[0]).bits());

                        dst[1] = dst[0];
                        dst[2] = dst[0];
                        dst[3] = dst[0];
                        dst[4] = dst[0];
                        dst[5] = dst[0];
                        dst[6] = dst[0];
                        dst[7] = dst[0];

                    #else

                        unsigned short *dst = &rowBlock[comp][blockx*64];

                        dst[0] = ((half)_dctData[comp]._buffer[0]).bits();

                        for (int i = 1; i < 64; ++i)
                        {
                            dst[i] = dst[0];
                        }

                    #endif
                }
            }
        }


        for (size_t comp = 0; comp < numComp; ++comp)
        {


        #ifdef IMF_HAVE_SSE2

            bool fastPath = true;

            for (int y = 8 * blocky; y < 8 * blocky + maxY; ++y)
            {
                if (reinterpret_cast<uintptr_t>(_rowPtrs[comp][y]) & _SSE_ALIGNMENT_MASK)
                    fastPath = false;
            }

            if (fastPath)
            {


                for (int y=8*blocky; y<8*blocky+maxY; ++y)
                {
                    __m128i *dst = (__m128i *)_rowPtrs[comp][y];
                    __m128i *src = (__m128i *)&rowBlock[comp][(y & 0x7) * 8];


                    for (int blockx = 0; blockx < numFullBlocksX; ++blockx)
                    {


                        _mm_prefetch ((char *)(src + 16), _MM_HINT_NTA);

                        unsigned short i0  = _mm_extract_epi16 (*src, 0);
                        unsigned short i1  = _mm_extract_epi16 (*src, 1);
                        unsigned short i2  = _mm_extract_epi16 (*src, 2);
                        unsigned short i3  = _mm_extract_epi16 (*src, 3);

                        unsigned short i4  = _mm_extract_epi16 (*src, 4);
                        unsigned short i5  = _mm_extract_epi16 (*src, 5);
                        unsigned short i6  = _mm_extract_epi16 (*src, 6);
                        unsigned short i7  = _mm_extract_epi16 (*src, 7);

                        i0 = _toLinear[i0];
                        i1 = _toLinear[i1];
                        i2 = _toLinear[i2];
                        i3 = _toLinear[i3];

                        i4 = _toLinear[i4];
                        i5 = _toLinear[i5];
                        i6 = _toLinear[i6];
                        i7 = _toLinear[i7];

                        *dst = _mm_insert_epi16 (_mm_setzero_si128(), i0, 0);
                        *dst = _mm_insert_epi16 (*dst, i1, 1);
                        *dst = _mm_insert_epi16 (*dst, i2, 2);
                        *dst = _mm_insert_epi16 (*dst, i3, 3);

                        *dst = _mm_insert_epi16 (*dst, i4, 4);
                        *dst = _mm_insert_epi16 (*dst, i5, 5);
                        *dst = _mm_insert_epi16 (*dst, i6, 6);
                        *dst = _mm_insert_epi16 (*dst, i7, 7);

                        src += 8;
                        dst++;
                    }
                }
            }
            else
            {

        #endif


                for (int y = 8 * blocky; y < 8 * blocky + maxY; ++y)
                {
                    unsigned short *dst = (unsigned short *)_rowPtrs[comp][y];

                    for (int blockx = 0; blockx < numFullBlocksX; ++blockx)
                    {
                        unsigned short *src =
                            &rowBlock[comp][blockx * 64 + ((y & 0x7) * 8)];

                        dst[0] = _toLinear[src[0]];
                        dst[1] = _toLinear[src[1]];
                        dst[2] = _toLinear[src[2]];
                        dst[3] = _toLinear[src[3]];

                        dst[4] = _toLinear[src[4]];
                        dst[5] = _toLinear[src[5]];
                        dst[6] = _toLinear[src[6]];
                        dst[7] = _toLinear[src[7]];

                        dst += 8;
                    }
                }

        #ifdef IMF_HAVE_SSE2

            }

        #endif


            if (numFullBlocksX != numBlocksX)
            {
                for (int y = 8 * blocky; y < 8 * blocky + maxY; ++y)
                {
                    unsigned short *src = (unsigned short *)
                        &rowBlock[comp][numFullBlocksX * 64 + ((y & 0x7) * 8)];

                    unsigned short *dst = (unsigned short *)_rowPtrs[comp][y];

                    dst += 8 * numFullBlocksX;

                    for (int x = 0; x < maxX; ++x)
                    {
                        *dst++ = _toLinear[*src++];
                    }
                }
            }
        }
    }


    for (size_t chan = 0; chan < numComp; ++chan)
    {

        if (_type[chan] != FLOAT)
            continue;

        std::vector<unsigned short> halfXdr (_width);

        for (int y=0; y<_height; ++y)
        {
            char *floatXdrPtr = _rowPtrs[chan][y];

            memcpy(&halfXdr[0], floatXdrPtr, _width*sizeof(unsigned short));

            const char *halfXdrPtr = (const char *)(&halfXdr[0]);

            for (int x=0; x<_width; ++x)
            {
                half tmpHalf;

                Xdr::read<CharPtrIO> (halfXdrPtr, tmpHalf);
                Xdr::write<CharPtrIO> (floatXdrPtr, (float)tmpHalf);


            }
        }
    }

    delete[] rowBlockHandle;
}
