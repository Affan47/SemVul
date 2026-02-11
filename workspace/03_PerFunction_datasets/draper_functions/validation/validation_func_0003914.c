val_dsp_name_ext_args(
    OM_uint32 *minor_status,
    gss_name_t input_name,
    gss_OID display_as_name_type,
    gss_buffer_t output_name_buffer)
{


    if (minor_status != NULL)
        *minor_status = 0;

    if (output_name_buffer != GSS_C_NO_BUFFER) {
        output_name_buffer->length = 0;
        output_name_buffer->value = NULL;
    }


    if (minor_status == NULL)
        return GSS_S_CALL_INACCESSIBLE_WRITE;

    if (output_name_buffer == GSS_C_NO_BUFFER)
        return GSS_S_CALL_INACCESSIBLE_WRITE;

    if (input_name == GSS_C_NO_NAME)
        return GSS_S_CALL_INACCESSIBLE_READ | GSS_S_BAD_NAME;

    if (display_as_name_type == GSS_C_NO_OID)
        return GSS_S_CALL_INACCESSIBLE_READ | GSS_S_BAD_NAMETYPE;

    return GSS_S_COMPLETE;
}
