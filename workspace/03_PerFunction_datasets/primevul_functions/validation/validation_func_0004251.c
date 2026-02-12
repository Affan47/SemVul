static void pb_field_set_to_default(pb_field_iter_t *iter)
{
    pb_type_t type;
    type = iter->pos->type;

    if (PB_LTYPE(type) == PB_LTYPE_EXTENSION)
    {
        pb_extension_t *ext = *(pb_extension_t* const *)iter->pData;
        while (ext != NULL)
        {
            pb_field_iter_t ext_iter;
            ext->found = false;
            iter_from_extension(&ext_iter, ext);
            pb_field_set_to_default(&ext_iter);
            ext = ext->next;
        }
    }
    else if (PB_ATYPE(type) == PB_ATYPE_STATIC)
    {
        bool init_data = true;
        if (PB_HTYPE(type) == PB_HTYPE_OPTIONAL && iter->pSize != iter->pData)
        {


            *(bool*)iter->pSize = false;
        }
        else if (PB_HTYPE(type) == PB_HTYPE_REPEATED ||
                 PB_HTYPE(type) == PB_HTYPE_ONEOF)
        {


            *(pb_size_t*)iter->pSize = 0;
            init_data = false;
        }

        if (init_data)
        {
            if (PB_LTYPE(iter->pos->type) == PB_LTYPE_SUBMESSAGE)
            {

                pb_message_set_to_defaults((const pb_field_t *) iter->pos->ptr, iter->pData);
            }
            else if (iter->pos->ptr != NULL)
            {

                memcpy(iter->pData, iter->pos->ptr, iter->pos->data_size);
            }
            else
            {

                memset(iter->pData, 0, iter->pos->data_size);
            }
        }
    }
    else if (PB_ATYPE(type) == PB_ATYPE_POINTER)
    {

        *(void**)iter->pData = NULL;


        if (PB_HTYPE(type) == PB_HTYPE_REPEATED ||
            PB_HTYPE(type) == PB_HTYPE_ONEOF)
        {
            *(pb_size_t*)iter->pSize = 0;
        }
    }
    else if (PB_ATYPE(type) == PB_ATYPE_CALLBACK)
    {

    }
}
