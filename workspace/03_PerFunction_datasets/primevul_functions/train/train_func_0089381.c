static bool checkreturn pb_dec_submessage(pb_istream_t *stream, const pb_field_iter_t *field)
{
    bool status = true;
    pb_istream_t substream;

    if (!pb_make_string_substream(stream, &substream))
        return false;

    if (field->submsg_desc == NULL)
        PB_RETURN_ERROR(stream, "invalid field descriptor");


    if (PB_HTYPE(field->type) == PB_HTYPE_REPEATED ||
        PB_HTYPE(field->type) == PB_HTYPE_ONEOF)
    {
        pb_field_iter_t submsg_iter;
        if (pb_field_iter_begin(&submsg_iter, field->submsg_desc, field->pData))
        {
            if (!pb_message_set_to_defaults(&submsg_iter))
                PB_RETURN_ERROR(stream, "failed to set defaults");
        }
    }


    if (PB_LTYPE(field->type) == PB_LTYPE_SUBMSG_W_CB && field->pSize != NULL)
    {

        pb_callback_t *callback = (pb_callback_t*)field->pSize - 1;
        if (callback->funcs.decode)
        {
            status = callback->funcs.decode(&substream, field, &callback->arg);
        }
    }


    if (status)
    {
        status = pb_decode_inner(&substream, field->submsg_desc, field->pData, 0);
    }

    if (!pb_close_string_substream(stream, &substream))
        return false;

    return status;
}
