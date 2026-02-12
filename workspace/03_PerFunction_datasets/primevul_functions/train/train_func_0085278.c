static unsigned char *MakeAdtsHeader(int *dataSize, NeAACDecFrameInfo *hInfo, int old_format)
{
    unsigned char *data;
    int profile = (hInfo->object_type - 1) & 0x3;
    int sr_index = ((hInfo->sbr == SBR_UPSAMPLED) || (hInfo->sbr == NO_SBR_UPSAMPLED)) ?
        FindAdtsSRIndex(hInfo->samplerate / 2) : FindAdtsSRIndex(hInfo->samplerate);
    int skip = (old_format) ? 8 : 7;
    int framesize = skip + hInfo->bytesconsumed;

    if (hInfo->header_type == ADTS)
        framesize -= skip;

    *dataSize = 7;

    data = malloc(*dataSize * sizeof(unsigned char));
    memset(data, 0, *dataSize * sizeof(unsigned char));

    data[0] += 0xFF;

    data[1] += 0xF0;


    data[1] += 1;

    data[2] += ((profile << 6) & 0xC0);
    data[2] += ((sr_index << 2) & 0x3C);

    data[2] += ((hInfo->channels >> 2) & 0x1);

    data[3] += ((hInfo->channels << 6) & 0xC0);


    data[3] += ((framesize >> 11) & 0x3);

    data[4] += ((framesize >> 3) & 0xFF);

    data[5] += ((framesize << 5) & 0xE0);
    data[5] += ((0x7FF >> 6) & 0x1F);

    data[6] += ((0x7FF << 2) & 0x3F);


    return data;
}
