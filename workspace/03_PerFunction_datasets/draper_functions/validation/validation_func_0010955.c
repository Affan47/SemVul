HexConvert_S32(HexDialogVal64 *val, HexConversionProperties *prop)
{
    guchar in[4];
    int i, local = 0;
    if (prop->endian == LITTLE)
    {
        in[0] = val->v[0];
        in[1] = val->v[1];
        in[2] = val->v[2];
        in[3] = val->v[3];
    }
    else
    {
        in[0] = val->v[3];
        in[1] = val->v[2];
        in[2] = val->v[1];
        in[3] = val->v[0];
    }
    for (i = 0; i < 8; i++)
        local += ((in[0] >> i) & 0x1) * pow2(i);
    for (i = 0; i < 8; i++)
        local += ((in[1] >> i) & 0x1) * pow2(i + 8);
    for (i = 0; i < 8; i++)
        local += ((in[2] >> i) & 0x1) * pow2(i + 16);
    for (i = 0; i < 7; i++)
        local += ((in[3] >> i) & 0x1) * pow2(i + 24);
    if ((in[3] >> 7) & 0x1)
        local  = -(pow2(31) - local);
    snprintf(convbuffer, sizeof(convbuffer), "%d", local);
    return convbuffer;
}
