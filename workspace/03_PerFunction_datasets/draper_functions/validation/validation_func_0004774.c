PHP_WHIRLPOOLUpdate(PHP_WHIRLPOOL_CTX *context, const unsigned char *input, size_t len)
{
    php_hash_uint64 sourceBits = len * 8;
    int sourcePos    = 0;
    int sourceGap    = (8 - ((int)sourceBits & 7)) & 7;
    int bufferRem    = context->buffer.bits & 7;
    const unsigned char *source = input;
    unsigned char *buffer       = context->buffer.data;
    unsigned char *bitLength    = context->bitlength;
    int bufferBits   = context->buffer.bits;
    int bufferPos    = context->buffer.pos;
    php_hash_uint32 b, carry;
    int i;


    php_hash_uint64 value = sourceBits;
    for (i = 31, carry = 0; i >= 0 && (carry != 0 || value != L64(0)); i--) {
        carry += bitLength[i] + ((php_hash_uint32)value & 0xff);
        bitLength[i] = (unsigned char)carry;
        carry >>= 8;
        value >>= 8;
    }


    while (sourceBits > 8) {


        b = ((source[sourcePos] << sourceGap) & 0xff) |
            ((source[sourcePos + 1] & 0xff) >> (8 - sourceGap));


        buffer[bufferPos++] |= (unsigned char)(b >> bufferRem);
        bufferBits += 8 - bufferRem;
        if (bufferBits == DIGESTBITS) {


            WhirlpoolTransform(context);


            bufferBits = bufferPos = 0;
        }
        buffer[bufferPos] = (unsigned char) (b << (8 - bufferRem));
        bufferBits += bufferRem;


        sourceBits -= 8;
        sourcePos++;
    }


    if (sourceBits > 0) {
        b = (source[sourcePos] << sourceGap) & 0xff;


        buffer[bufferPos] |= b >> bufferRem;
    } else {
        b = 0;
    }
    if (bufferRem + sourceBits < 8) {


        bufferBits += (int) sourceBits;
    } else {


        bufferPos++;
        bufferBits += 8 - bufferRem;
        sourceBits -= 8 - bufferRem;


        if (bufferBits == DIGESTBITS) {


            WhirlpoolTransform(context);


            bufferBits = bufferPos = 0;
        }
        buffer[bufferPos] = (unsigned char) (b << (8 - bufferRem));
        bufferBits += (int)sourceBits;
    }
    context->buffer.bits   = bufferBits;
    context->buffer.pos    = bufferPos;
}
