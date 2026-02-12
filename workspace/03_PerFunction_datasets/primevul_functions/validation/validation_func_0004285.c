bool pb_decode_double_as_float(pb_istream_t *stream, float *dest)
{
    uint_least8_t sign;
    int exponent;
    uint32_t mantissa;
    uint64_t value;
    union { float f; uint32_t i; } out;

    if (!pb_decode_fixed64(stream, &value))
        return false;


    sign = (uint_least8_t)((value >> 63) & 1);
    exponent = (int)((value >> 52) & 0x7FF) - 1023;
    mantissa = (value >> 28) & 0xFFFFFF;


    if (exponent == 1024)
    {

        exponent = 128;
        mantissa >>= 1;
    }
    else
    {
        if (exponent > 127)
        {

            exponent = 128;
            mantissa = 0;
        }
        else if (exponent < -150)
        {

            exponent = -127;
            mantissa = 0;
        }
        else if (exponent < -126)
        {

            mantissa |= 0x1000000;
            mantissa >>= (-126 - exponent);
            exponent = -127;
        }


        mantissa = (mantissa + 1) >> 1;


        if (mantissa & 0x800000)
        {
            exponent += 1;
            mantissa &= 0x7FFFFF;
            mantissa >>= 1;
        }
    }


    out.i = mantissa;
    out.i |= (uint32_t)(exponent + 127) << 23;
    out.i |= (uint32_t)sign << 31;

    *dest = out.f;
    return true;
}
