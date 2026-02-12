int WavInFile::readHeaderBlock()
{
    char label[5];
    string sLabel;


    if (fread(label, 1, 4, fptr) !=4) return -1;
    label[4] = 0;

    if (isAlphaStr(label) == 0) return -1;


    if (strcmp(label, fmtStr) == 0)
    {
        int nLen, nDump;


        memcpy(header.format.fmt, fmtStr, 4);


        if (fread(&nLen, sizeof(int), 1, fptr) != 1) return -1;

        _swap32(nLen);


        if (nLen < sizeof(header.format) - 8) return -1;

        header.format.format_len = nLen;


        nDump = nLen - ((int)sizeof(header.format) - 8);


        if (nDump > 0)
        {
            nLen = sizeof(header.format) - 8;
        }


        if (fread(&(header.format.fixed), nLen, 1, fptr) != 1) return -1;


        _swap16((short &)header.format.fixed);
        _swap16((short &)header.format.channel_number);
        _swap32((int &)header.format.sample_rate);
        _swap32((int &)header.format.byte_rate);
        _swap16((short &)header.format.byte_per_sample);
        _swap16((short &)header.format.bits_per_sample);


        if (nDump > 0)
        {
            fseek(fptr, nDump, SEEK_CUR);
        }

        return 0;
    }
    else if (strcmp(label, factStr) == 0)
    {
        int nLen, nDump;


        memcpy(header.fact.fact_field, factStr, 4);


        if (fread(&nLen, sizeof(int), 1, fptr) != 1) return -1;

        _swap32(nLen);


        if (nLen < sizeof(header.fact) - 8) return -1;

        header.fact.fact_len = nLen;


        nDump = nLen - ((int)sizeof(header.fact) - 8);


        if (nDump > 0)
        {
            nLen = sizeof(header.fact) - 8;
        }


        if (fread(&(header.fact.fact_sample_len), nLen, 1, fptr) != 1) return -1;


        _swap32((int &)header.fact.fact_sample_len);


        if (nDump > 0)
        {
            fseek(fptr, nDump, SEEK_CUR);
        }

        return 0;
    }
    else if (strcmp(label, dataStr) == 0)
    {

        memcpy(header.data.data_field, dataStr, 4);
        if (fread(&(header.data.data_len), sizeof(uint), 1, fptr) != 1) return -1;


        _swap32((int &)header.data.data_len);

        return 1;
    }
    else
    {
        uint len, i;
        uint temp;


        if (fread(&len, sizeof(len), 1, fptr) != 1) return -1;

        for (i = 0; i < len; i ++)
        {
            if (fread(&temp, 1, 1, fptr) != 1) return -1;
            if (feof(fptr)) return -1;
        }
    }
    return 0;
}
