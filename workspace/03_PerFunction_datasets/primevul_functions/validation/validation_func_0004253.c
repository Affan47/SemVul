bool checkreturn pb_decode_noinit(pb_istream_t *stream, const pb_field_t fields[], void *dest_struct)
{
    uint32_t fields_seen[(PB_MAX_REQUIRED_FIELDS + 31) / 32] = {0, 0};
    const uint32_t allbits = ~(uint32_t)0;
    uint32_t extension_range_start = 0;
    pb_field_iter_t iter;


    const pb_field_t *fixed_count_field = NULL;
    pb_size_t fixed_count_size = 0;


    (void)pb_field_iter_begin(&iter, fields, dest_struct);

    while (stream->bytes_left)
    {
        uint32_t tag;
        pb_wire_type_t wire_type;
        bool eof;

        if (!pb_decode_tag(stream, &wire_type, &tag, &eof))
        {
            if (eof)
                break;
            else
                return false;
        }

        if (!pb_field_iter_find(&iter, tag))
        {

            if (tag >= extension_range_start)
            {
                if (!find_extension_field(&iter))
                    extension_range_start = (uint32_t)-1;
                else
                    extension_range_start = iter.pos->tag;

                if (tag >= extension_range_start)
                {
                    size_t pos = stream->bytes_left;

                    if (!decode_extension(stream, tag, wire_type, &iter))
                        return false;

                    if (pos != stream->bytes_left)
                    {

                        continue;
                    }
                }
            }


            if (!pb_skip_field(stream, wire_type))
                return false;
            continue;
        }


        if (PB_HTYPE(iter.pos->type) == PB_HTYPE_REPEATED
            && iter.pSize == iter.pData)
        {
            if (fixed_count_field != iter.pos) {


                if (fixed_count_field != NULL &&
                    fixed_count_size != fixed_count_field->array_size)
                {
                    PB_RETURN_ERROR(stream, "wrong size for fixed count field");
                }

                fixed_count_field = iter.pos;
                fixed_count_size = 0;
            }

            iter.pSize = &fixed_count_size;
        }

        if (PB_HTYPE(iter.pos->type) == PB_HTYPE_REQUIRED
            && iter.required_field_index < PB_MAX_REQUIRED_FIELDS)
        {
            uint32_t tmp = ((uint32_t)1 << (iter.required_field_index & 31));
            fields_seen[iter.required_field_index >> 5] |= tmp;
        }

        if (!decode_field(stream, wire_type, &iter))
            return false;
    }


    if (fixed_count_field != NULL &&
        fixed_count_size != fixed_count_field->array_size)
    {
        PB_RETURN_ERROR(stream, "wrong size for fixed count field");
    }


    {


        unsigned req_field_count;
        pb_type_t last_type;
        unsigned i;
        do {
            req_field_count = iter.required_field_index;
            last_type = iter.pos->type;
        } while (pb_field_iter_next(&iter));


        if (PB_HTYPE(last_type) == PB_HTYPE_REQUIRED && iter.pos->tag != 0)
            req_field_count++;

        if (req_field_count > PB_MAX_REQUIRED_FIELDS)
            req_field_count = PB_MAX_REQUIRED_FIELDS;

        if (req_field_count > 0)
        {

            for (i = 0; i < (req_field_count >> 5); i++)
            {
                if (fields_seen[i] != allbits)
                    PB_RETURN_ERROR(stream, "missing required field");
            }


            if ((req_field_count & 31) != 0)
            {
                if (fields_seen[req_field_count >> 5] !=
                    (allbits >> (32 - (req_field_count & 31))))
                {
                    PB_RETURN_ERROR(stream, "missing required field");
                }
            }
        }
    }

    return true;
}
