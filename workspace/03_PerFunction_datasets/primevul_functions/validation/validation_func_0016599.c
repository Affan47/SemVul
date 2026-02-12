FastHufDecoder::refill
    (Int64 &buffer,
     int numBits,
     Int64 &bufferBack,
     int &bufferBackNumBits,
     const unsigned char *&currByte,
     int &currBitsLeft)
{


    buffer |= bufferBack >> (64 - numBits);

    if (bufferBackNumBits < numBits)
    {
        numBits -= bufferBackNumBits;


        if (currBitsLeft >= 64)
        {
            bufferBack        = READ64 (currByte);
            bufferBackNumBits = 64;
            currByte         += sizeof (Int64);
            currBitsLeft     -= 8 * sizeof (Int64);

        }
        else
        {
            bufferBack        = 0;
            bufferBackNumBits = 64;

            Int64 shift = 56;

            while (currBitsLeft > 0)
            {
                bufferBack |= ((Int64)(*currByte)) << shift;

                currByte++;
                shift        -= 8;
                currBitsLeft -= 8;
            }


            if (currBitsLeft < 0)
                currBitsLeft = 0;
        }

        buffer |= bufferBack >> (64 - numBits);
    }

    bufferBack         = bufferBack << numBits;
    bufferBackNumBits -= numBits;


    if (bufferBackNumBits == 0)
        bufferBack = 0;
}
