static void pb_release_single_field(pb_field_iter_t *field)
{
    pb_type_t type;
    type = field->type;

    if (PB_HTYPE(type) == PB_HTYPE_ONEOF)
    {
        if (*(pb_size_t*)field->pSize != field->tag)
            return;
    }


    if (PB_LTYPE(type) == PB_LTYPE_EXTENSION)
    {

        pb_extension_t *ext = *(pb_extension_t**)field->pData;
        while (ext != NULL)
        {
            pb_field_iter_t ext_iter;
            if (pb_field_iter_begin_extension(&ext_iter, ext))
            {
                pb_release_single_field(&ext_iter);
            }
            ext = ext->next;
        }
    }
    else if (PB_LTYPE_IS_SUBMSG(type) && PB_ATYPE(type) != PB_ATYPE_CALLBACK)
    {

        pb_size_t count = 1;

        if (PB_ATYPE(type) == PB_ATYPE_POINTER)
        {
            field->pData = *(void**)field->pField;
        }
        else
        {
            field->pData = field->pField;
        }

        if (PB_HTYPE(type) == PB_HTYPE_REPEATED)
        {
            count = *(pb_size_t*)field->pSize;

            if (PB_ATYPE(type) == PB_ATYPE_STATIC && count > field->array_size)
            {

                count = field->array_size;
            }
        }

        if (field->pData)
        {
            for (; count > 0; count--)
            {
                pb_release(field->submsg_desc, field->pData);
                field->pData = (char*)field->pData + field->data_size;
            }
        }
    }

    if (PB_ATYPE(type) == PB_ATYPE_POINTER)
    {
        if (PB_HTYPE(type) == PB_HTYPE_REPEATED &&
            (PB_LTYPE(type) == PB_LTYPE_STRING ||
             PB_LTYPE(type) == PB_LTYPE_BYTES))
        {

            void **pItem = *(void***)field->pField;
            pb_size_t count = *(pb_size_t*)field->pSize;
            for (; count > 0; count--)
            {
                pb_free(*pItem);
                *pItem++ = NULL;
            }
        }

        if (PB_HTYPE(type) == PB_HTYPE_REPEATED)
        {

            *(pb_size_t*)field->pSize = 0;
        }


        pb_free(*(void**)field->pField);
        *(void**)field->pField = NULL;
    }
}
