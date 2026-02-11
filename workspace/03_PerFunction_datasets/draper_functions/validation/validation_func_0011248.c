HPDF_MemStream_InWrite  (HPDF_Stream      stream,
                         const HPDF_BYTE  **ptr,
                         HPDF_UINT        *count)
{
    HPDF_MemStreamAttr attr = (HPDF_MemStreamAttr)stream->attr;
    HPDF_UINT rsize = attr->buf_siz - attr->w_pos;

    HPDF_PTRACE((" HPDF_MemStream_InWrite\n"));

    if (*count <= 0)
        return HPDF_OK;

    if (rsize >= *count) {
        HPDF_MemCpy (attr->w_ptr, *ptr, *count);
        attr->w_ptr += *count;
        attr->w_pos += *count;
        *count = 0;
    } else {
        if (rsize > 0) {
            HPDF_MemCpy (attr->w_ptr, *ptr, rsize);
            *ptr += rsize;
            *count -= rsize;
        }
        attr->w_ptr = (HPDF_BYTE*)HPDF_GetMem (stream->mmgr, attr->buf_siz);

        if (attr->w_ptr == NULL)
           return HPDF_Error_GetCode (stream->error);

        if (HPDF_List_Add (attr->buf, attr->w_ptr) != HPDF_OK) {
            HPDF_FreeMem (stream->mmgr, attr->w_ptr);
            attr->w_ptr = NULL;

            return HPDF_Error_GetCode (stream->error);
        }
        attr->w_pos = 0;
    }
    return HPDF_OK;
}
