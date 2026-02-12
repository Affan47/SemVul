decode_ne_resource_id (WinLibrary *fi, WinResource *wr, uint16_t value)
{
    if (value & NE_RESOURCE_NAME_IS_NUMERIC) {

        snprintf(wr->id, WINRES_ID_MAXLEN, "%d", value & ~NE_RESOURCE_NAME_IS_NUMERIC);
    } else {
        unsigned char len;
        char *mem = (char *) NE_HEADER(fi->memory)
                             + NE_HEADER(fi->memory)->rsrctab
                             + value;


        RETURN_IF_BAD_POINTER(false, *mem);
        len = mem[0];
        RETURN_IF_BAD_OFFSET(false, &mem[1], sizeof(char) * len);
        memcpy(wr->id, &mem[1], len);
        wr->id[len] = '\0';
    }

    wr->numeric_id = (value & NE_RESOURCE_NAME_IS_NUMERIC ? true:false);
    return true;
}
