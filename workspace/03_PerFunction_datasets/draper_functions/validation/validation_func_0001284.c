WriteUINT16 (HPDF_Stream   stream,
             HPDF_UINT16   value)
{
    HPDF_STATUS ret;
    HPDF_UINT16 tmp = value;

    UINT16Swap (&tmp);

    ret = HPDF_Stream_Write (stream, (HPDF_BYTE *)&tmp, sizeof(tmp));
    if (ret != HPDF_OK)
        return ret;

    return HPDF_OK;
}
