OutputArchStrToInt(const char *temp)
{
    int     i;
    char    outputArchKeywordTable[8][15] = { "NATIVE", "STD", "IEEE", "INTEL",
            "CRAY", "MIPS", "ALPHA", "UNIX" };
    for (i = 0; i < 8; i++)
        if (!HDstrcmp(outputArchKeywordTable[i], temp))
            return i;
    return -1;
}
