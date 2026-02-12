bool pb_decode_nullterminated(pb_istream_t *stream, const pb_field_t fields[], void *dest_struct)
{

    return pb_decode(stream, fields, dest_struct);
}
