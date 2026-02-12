FastHufDecoder::readBits
    (int numBits,
     Int64 &buffer,
     int &bufferNumBits,
     const char *&currByte)
{
    while (bufferNumBits < numBits)
    {
        buffer = (buffer << 8) | *(unsigned char*)(currByte++);
        bufferNumBits += 8;
    }

    bufferNumBits -= numBits;
    return (buffer >> bufferNumBits) & ((1 << numBits) - 1);
}
