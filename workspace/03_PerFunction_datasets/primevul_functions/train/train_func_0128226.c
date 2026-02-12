const char* LibRaw::HassyRawFormat_idx2HR(unsigned idx)
{
    for (int i = 0; i < sizeof HassyRawFormat / sizeof *HassyRawFormat; i++)
        if(HassyRawFormat[i].idx == idx)
            return HassyRawFormat[i].FormatName;
    return 0;
}
