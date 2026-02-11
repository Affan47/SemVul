GetLength(const byte* input, word32* inOutIdx, int* len)
{
    int     length = 0;
    word32  i = *inOutIdx;

    byte b = input[i++];
    if (b >= ASN_LONG_LENGTH) {
        word32 bytes = b & 0x7F;

        while (bytes--) {
            b = input[i++];
            length = (length << 8) | b;
        }
    }
    else
        length = b;

    *inOutIdx = i;
    *len      = length;

    return length;
}
