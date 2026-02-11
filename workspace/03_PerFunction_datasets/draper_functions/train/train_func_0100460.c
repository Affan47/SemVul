cli_bcapi_entropy_buffer(struct cli_bc_ctx *ctx , uint8_t* s, int32_t len)
{
    uint32_t probTable[256];
    unsigned int i;
    double entropy = 0;
    double log2 = log(2);

    UNUSEDPARAM(ctx);

    if (!s || len <= 0)
        return -1;
    memset(probTable, 0, sizeof(probTable));
    for (i=0;i<(unsigned int)len;i++) {
        probTable[s[i]]++;
    }
    for (i=0;i<256;i++) {
        double p;
        if (!probTable[i])
            continue;
        p = (double)probTable[i] / len;
        entropy += -p*log(p)/log2;
    }
    entropy *= 1<<26;
    return (uint32_t)entropy;
}
