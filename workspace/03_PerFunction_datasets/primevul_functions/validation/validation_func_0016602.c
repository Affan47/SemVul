FastHufDecoder::decode
    (const unsigned char *src,
     int numSrcBits,
     unsigned short *dst,
     int numDstElems)
{
    if (numSrcBits < 128)
        throw IEX_NAMESPACE::InputExc ("Error choosing Huffman decoder implementation "
                                       "(insufficient number of bits).");


    const unsigned char *currByte = src + 2 * sizeof (Int64);

    numSrcBits -= 8 * 2 * sizeof (Int64);


    Int64 buffer            = READ64 (src);
    int   bufferNumBits     = 64;


    Int64 bufferBack        = READ64 ((src + sizeof (Int64)));
    int   bufferBackNumBits = 64;

    int dstIdx = 0;

    while (dstIdx < numDstElems)
    {
        int  codeLen;
        int  symbol;


        if (_tableMin <= buffer)
        {
            int tableIdx = buffer >> (64 - TABLE_LOOKUP_BITS);


            codeLen = _tableCodeLen[tableIdx];
            symbol  = _tableSymbol[tableIdx];
        }
        else
        {
            if (bufferNumBits < 64)
            {
                refill (buffer,
                        64 - bufferNumBits,
                        bufferBack,
                        bufferBackNumBits,
                        currByte,
                        numSrcBits);

                bufferNumBits = 64;
            }


            codeLen = TABLE_LOOKUP_BITS + 1;

            while (_ljBase[codeLen] > buffer && codeLen <= _maxCodeLength)
                codeLen++;

            if (codeLen > _maxCodeLength)
            {
                throw IEX_NAMESPACE::InputExc ("Huffman decode error "
                                               "(Decoded an invalid symbol).");
            }

            Int64 id = _ljOffset[codeLen] + (buffer >> (64 - codeLen));
            if (id < static_cast<Int64>(_numSymbols))
            {
                symbol = _idToSymbol[id];
            }
            else
            {
                throw IEX_NAMESPACE::InputExc ("Huffman decode error "
                                               "(Decoded an invalid symbol).");
            }
        }


        buffer = buffer << codeLen;
        bufferNumBits -= codeLen;


        if (symbol == _rleSymbol)
        {
            if (bufferNumBits < 8)
            {
                refill (buffer,
                        64 - bufferNumBits,
                        bufferBack,
                        bufferBackNumBits,
                        currByte,
                        numSrcBits);

                bufferNumBits = 64;
            }

            int rleCount = buffer >> 56;

            if (dstIdx < 1)
            {
                throw IEX_NAMESPACE::InputExc ("Huffman decode error (RLE code "
                                               "with no previous symbol).");
            }

            if (dstIdx + rleCount > numDstElems)
            {
                throw IEX_NAMESPACE::InputExc ("Huffman decode error (Symbol run "
                                               "beyond expected output buffer length).");
            }

            if (rleCount <= 0)
            {
                throw IEX_NAMESPACE::InputExc("Huffman decode error"
                                              " (Invalid RLE length)");
            }

            for (int i = 0; i < rleCount; ++i)
                dst[dstIdx + i] = dst[dstIdx - 1];

            dstIdx += rleCount;

            buffer = buffer << 8;
            bufferNumBits -= 8;
        }
        else
        {
            dst[dstIdx] = symbol;
            dstIdx++;
        }


        if (bufferNumBits < TABLE_LOOKUP_BITS)
        {
            refill (buffer,
                    64 - bufferNumBits,
                    bufferBack,
                    bufferBackNumBits,
                    currByte,
                    numSrcBits);

            bufferNumBits = 64;
        }
    }

    if (numSrcBits != 0)
    {
        throw IEX_NAMESPACE::InputExc ("Huffman decode error (Compressed data remains "
                                       "after filling expected output buffer).");
    }
}
