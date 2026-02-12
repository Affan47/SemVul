static void pb_message_set_to_defaults(const pb_field_t fields[], void *dest_struct)
{
    pb_field_iterator_t iter;
    pb_field_init(&iter, fields, dest_struct);

    do
    {
        pb_type_t type;
        type = iter.pos->type;


        if (iter.pos->tag == 0)
            continue;

        if (PB_ATYPE(type) == PB_ATYPE_STATIC)
        {
            if (PB_HTYPE(type) == PB_HTYPE_OPTIONAL)
            {


                *(bool*)iter.pSize = false;
            }
            else if (PB_HTYPE(type) == PB_HTYPE_REPEATED)
            {

                *(size_t*)iter.pSize = 0;
                continue;
            }

            if (PB_LTYPE(iter.pos->type) == PB_LTYPE_SUBMESSAGE)
            {

                pb_message_set_to_defaults((const pb_field_t *) iter.pos->ptr, iter.pData);
            }
            else if (iter.pos->ptr != NULL)
            {

                memcpy(iter.pData, iter.pos->ptr, iter.pos->data_size);
            }
            else
            {

                memset(iter.pData, 0, iter.pos->data_size);
            }
        }
        else if (PB_ATYPE(type) == PB_ATYPE_POINTER)
        {

            *(void**)iter.pData = NULL;


            if (PB_HTYPE(type) == PB_HTYPE_REPEATED)
            {
                *(size_t*)iter.pSize = 0;
            }
        }
        else if (PB_ATYPE(type) == PB_ATYPE_CALLBACK)
        {

        }
    } while (pb_field_next(&iter));
}
