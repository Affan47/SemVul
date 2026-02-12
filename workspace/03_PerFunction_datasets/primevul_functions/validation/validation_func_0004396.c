static void pb_release_single_field(const pb_field_iterator_t *iter)
{
    pb_type_t type;
    type = iter->pos->type;


    if (PB_LTYPE(type) == PB_LTYPE_EXTENSION)
    {

        pb_extension_t *ext = *(pb_extension_t**)iter->pData;
        while (ext != NULL)
        {
            pb_field_iterator_t ext_iter;
            iter_from_extension(&ext_iter, ext);
            pb_release_single_field(&ext_iter);
            ext = ext->next;
        }
    }
    else if (PB_LTYPE(type) == PB_LTYPE_SUBMESSAGE)
    {

        void *pItem = iter->pData;
        pb_size_t count = 1;

        if (PB_ATYPE(type) == PB_ATYPE_POINTER)
        {
            pItem = *(void**)iter->pData;
        }

        if (PB_HTYPE(type) == PB_HTYPE_REPEATED)
        {
            count = *(pb_size_t*)iter->pSize;

            if (PB_ATYPE(type) == PB_ATYPE_STATIC && count > iter->pos->array_size)
            {

                count = iter->pos->array_size;
            }
        }

        if (pItem)
        {
            while (count--)
            {
                pb_release((const pb_field_t*)iter->pos->ptr, pItem);
                pItem = (uint8_t*)pItem + iter->pos->data_size;
            }
        }
    }

    if (PB_ATYPE(type) == PB_ATYPE_POINTER)
    {
        if (PB_HTYPE(type) == PB_HTYPE_REPEATED &&
            (PB_LTYPE(type) == PB_LTYPE_STRING ||
             PB_LTYPE(type) == PB_LTYPE_BYTES))
        {

            void **pItem = *(void***)iter->pData;
            pb_size_t count = *(pb_size_t*)iter->pSize;
            while (count--)
            {
                pb_free(*pItem);
                *pItem++ = NULL;
            }
        }

        if (PB_HTYPE(type) == PB_HTYPE_REPEATED)
        {

            *(pb_size_t*)iter->pSize = 0;
        }


        pb_free(*(void**)iter->pData);
        *(void**)iter->pData = NULL;
    }
}
