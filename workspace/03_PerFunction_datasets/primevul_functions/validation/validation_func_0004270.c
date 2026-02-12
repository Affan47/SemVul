static bool checkreturn pb_dec_varint(pb_istream_t *stream, const pb_field_t *field, void *dest)
{
    pb_uint64_t value;
    pb_int64_t svalue;
    pb_int64_t clamped;
    if (!pb_decode_varint(stream, &value))
        return false;


    if (field->data_size == sizeof(pb_int64_t))
        svalue = (pb_int64_t)value;
    else
        svalue = (int32_t)value;


    if (field->data_size == sizeof(pb_int64_t))
        clamped = *(pb_int64_t*)dest = svalue;
    else if (field->data_size == sizeof(int32_t))
        clamped = *(int32_t*)dest = (int32_t)svalue;
    else if (field->data_size == sizeof(int_least16_t))
        clamped = *(int_least16_t*)dest = (int_least16_t)svalue;
    else if (field->data_size == sizeof(int_least8_t))
        clamped = *(int_least8_t*)dest = (int_least8_t)svalue;
    else
        PB_RETURN_ERROR(stream, "invalid data_size");

    if (clamped != svalue)
        PB_RETURN_ERROR(stream, "integer too large");

    return true;
}
