tga_pack_pixel(uint8_t *dest, const uint8_t bits,
    const uint8_t b, const uint8_t g, const uint8_t r, const uint8_t a)
{
    switch (bits)
    {
    case 32:
        dest[0] = b;
        dest[1] = g;
        dest[2] = r;
        dest[3] = a;
        break;

    case 24:
        dest[0] = b;
        dest[1] = g;
        dest[2] = r;
        break;

    case 16:
        {
            uint16_t tmp;

            #define FIVE_BITS (BIT(0)|BIT(1)|BIT(2)|BIT(3)|BIT(4))
            tmp  =  (b >> 3) & FIVE_BITS;
            tmp |= ((g >> 3) & FIVE_BITS) << 5;
            tmp |= ((r >> 3) & FIVE_BITS) << 10;
            if (a > 127) tmp |= BIT(15);
            #undef FIVE_BITS

            dest[0] = (uint8_t) (tmp & 0x00FF);
            dest[1] = (uint8_t)((tmp & 0xFF00) >> 8);
            break;
        }

    default:
        return TGAERR_PIXEL_DEPTH;
    }
    return TGA_NOERR;
}
