static void skip_header_chunk(EXRContext *s)
{
    GetByteContext *gb = &s->gb;

    while (bytestream2_get_bytes_left(gb) > 0) {
        if (!bytestream2_peek_byte(gb))
            break;


        for (int i = 0; i < 2; i++)
            while (bytestream2_get_byte(gb) != 0);


        bytestream2_skip(gb, bytestream2_get_le32(gb));
    }
}
