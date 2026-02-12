static bool checkreturn pb_dec_submessage(pb_istream_t *stream, const pb_field_iter_t *field)
{
    bool status = true;
    bool submsg_consumed = false;
    pb_istream_t substream;

    if (!pb_make_string_substream(stream, &substream))
        return false;

    if (field->submsg_desc == NULL)
        PB_RETURN_ERROR(stream, "invalid field descriptor");


    if (PB_LTYPE(field->type) == PB_LTYPE_SUBMSG_W_CB && field->pSize != NULL)
    {

        pb_callback_t *callback = (pb_callback_t*)field->pSize - 1;
        if (callback->funcs.decode)
        {
            status = callback->funcs.decode(&substream, field, &callback->arg);

            if (substream.bytes_left == 0)
            {
                submsg_consumed = true;
            }
        }
    }


    if (status && !submsg_consumed)
    {
        unsigned int flags = 0;


        if (PB_ATYPE(field->type) == PB_ATYPE_STATIC &&
            PB_HTYPE(field->type) != PB_HTYPE_REPEATED)
        {
            flags = PB_DECODE_NOINIT;
        }

        status = pb_decode_inner(&substream, field->submsg_desc, field->pData, flags);
    }

    if (!pb_close_string_substream(stream, &substream))
        return false;

    return status;
}
