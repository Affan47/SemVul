FastHufDecoder::FastHufDecoder
    (const char *&table,
     int numBytes,
     int minSymbol,
     int maxSymbol,
     int rleSymbol)
:
    _rleSymbol (rleSymbol),
    _numSymbols (0),
    _minCodeLength (255),
    _maxCodeLength (0),
    _idToSymbol (0)
{


    std::vector<Int64> symbols;


    Int64 base[MAX_CODE_LEN + 1];


    Int64 offset[MAX_CODE_LEN + 1];


    size_t codeCount[MAX_CODE_LEN + 1];

    for (int i = 0; i <= MAX_CODE_LEN; ++i)
    {
        codeCount[i] = 0;
        base[i]      = 0xffffffffffffffffULL;
        offset[i]    = 0;
    }


    const char *currByte     = table;
    Int64       currBits     = 0;
    int         currBitCount = 0;

    const int SHORT_ZEROCODE_RUN = 59;
    const int LONG_ZEROCODE_RUN  = 63;
    const int SHORTEST_LONG_RUN  = 2 + LONG_ZEROCODE_RUN - SHORT_ZEROCODE_RUN;

    for (Int64 symbol = static_cast<Int64>(minSymbol); symbol <= static_cast<Int64>(maxSymbol); symbol++)
    {
        if (currByte - table > numBytes)
        {
            throw IEX_NAMESPACE::InputExc ("Error decoding Huffman table "
                                           "(Truncated table data).");
        }


        Int64 codeLen = readBits (6, currBits, currBitCount, currByte);

        if (codeLen == (Int64) LONG_ZEROCODE_RUN)
        {
            if (currByte - table > numBytes)
            {
                throw IEX_NAMESPACE::InputExc ("Error decoding Huffman table "
                                               "(Truncated table data).");
            }

            int runLen = readBits (8, currBits, currBitCount, currByte) +
                         SHORTEST_LONG_RUN;

            if (symbol + runLen > static_cast<Int64>(maxSymbol + 1))
            {
                throw IEX_NAMESPACE::InputExc ("Error decoding Huffman table "
                                               "(Run beyond end of table).");
            }

            symbol += runLen - 1;

        }
        else if (codeLen >= static_cast<Int64>(SHORT_ZEROCODE_RUN))
        {
            int runLen = codeLen - SHORT_ZEROCODE_RUN + 2;

            if (symbol + runLen > static_cast<Int64>(maxSymbol + 1))
            {
                throw IEX_NAMESPACE::InputExc ("Error decoding Huffman table "
                                               "(Run beyond end of table).");
            }

            symbol += runLen - 1;

        }
        else if (codeLen != 0)
        {
            symbols.push_back ((symbol << 6) | (codeLen & 63));

            if (codeLen < _minCodeLength)
                _minCodeLength = codeLen;

            if (codeLen > _maxCodeLength)
                _maxCodeLength = codeLen;

            codeCount[codeLen]++;
        }
    }

    for (int i = 0; i < MAX_CODE_LEN; ++i)
        _numSymbols += codeCount[i];

    table = currByte;


    {
        double* countTmp = new double[_maxCodeLength+1];

        for (int l = _minCodeLength; l <= _maxCodeLength; ++l)
        {
            countTmp[l] = (double)codeCount[l] *
                          (double)(2 << (_maxCodeLength-l));
        }

        for (int l = _minCodeLength; l <= _maxCodeLength; ++l)
        {
            double tmp = 0;

            for (int k =l + 1; k <= _maxCodeLength; ++k)
                tmp += countTmp[k];

            tmp /= (double)(2 << (_maxCodeLength - l));

            base[l] = (Int64)ceil (tmp);
        }

        delete [] countTmp;
    }


    offset[_maxCodeLength] = 0;

    for (int i= _maxCodeLength - 1; i >= _minCodeLength; i--)
        offset[i] = offset[i + 1] + codeCount[i + 1];


    _idToSymbol = new int[_numSymbols];

    Int64 mapping[MAX_CODE_LEN + 1];
    for (int i = 0; i < MAX_CODE_LEN + 1; ++i)
        mapping[i] = -1;
    for (int i = _minCodeLength; i <= _maxCodeLength; ++i)
        mapping[i] = offset[i];

    for (std::vector<Int64>::const_iterator i = symbols.begin();
         i != symbols.end();
         ++i)
    {
        int codeLen = *i & 63;
        int symbol  = *i >> 6;

        if (mapping[codeLen] >= static_cast<Int64>(_numSymbols))
        {
            delete[] _idToSymbol;
            _idToSymbol = NULL;
            throw IEX_NAMESPACE::InputExc ("Huffman decode error "
                                           "(Invalid symbol in header).");
        }
        _idToSymbol[mapping[codeLen]] = symbol;
        mapping[codeLen]++;
    }


    try
    {
      buildTables(base, offset);
    }catch(...)
    {
            delete[] _idToSymbol;
            _idToSymbol = NULL;
            throw;
    }
}
