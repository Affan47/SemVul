static bool checkreturn pb_decode_varint32_eof(pb_istream_t *stream, uint32_t *dest, bool *eof)
{
    pb_byte_t byte;
    uint32_t result;

    if (!pb_readbyte(stream, &byte))
    {
        if (stream->bytes_left == 0)
        {
            if (eof)
            {
                *eof = true;
            }
        }

        return false;
    }

    if ((byte & 0x80) == 0)
    {

        result = byte;
    }
    else
    {

        uint_fast8_t bitpos = 7;
        result = byte & 0x7F;

        do
        {
            if (!pb_readbyte(stream, &byte))
                return false;

            if (bitpos >= 32)
            {

                pb_byte_t sign_extension = (bitpos < 63) ? 0xFF : 0x01;

                if ((byte & 0x7F) != 0x00 && ((result >> 31) == 0 || byte != sign_extension))
                {
                    PB_RETURN_ERROR(stream, "varint overflow");
                }
            }
            else
            {
                result |= (uint32_t)(byte & 0x7F) << bitpos;
            }
            bitpos = (uint_fast8_t)(bitpos + 7);
        } while (byte & 0x80);

        if (bitpos == 35 && (byte & 0x70) != 0)
        {

            PB_RETURN_ERROR(stream, "varint overflow");
        }
   }

   *dest = result;
   return true;
}
