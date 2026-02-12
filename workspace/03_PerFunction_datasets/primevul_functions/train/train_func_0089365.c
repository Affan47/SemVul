static bool checkreturn pb_decode_inner(pb_istream_t *stream, const pb_msgdesc_t *fields, void *dest_struct, unsigned int flags)
{
    uint32_t extension_range_start = 0;


    pb_size_t fixed_count_field = PB_SIZE_MAX;
    pb_size_t fixed_count_size = 0;
    pb_size_t fixed_count_total_size = 0;

    pb_fields_seen_t fields_seen = {{0, 0}};
    const uint32_t allbits = ~(uint32_t)0;
    pb_field_iter_t iter;

    if (pb_field_iter_begin(&iter, fields, dest_struct))
    {
        if ((flags & PB_DECODE_NOINIT) == 0)
        {
            if (!pb_message_set_to_defaults(&iter))
                PB_RETURN_ERROR(stream, "failed to set defaults");
        }
    }

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

        if (tag == 0)
        {
          if (flags & PB_DECODE_NULLTERMINATED)
          {
            break;
          }
          else
          {
            PB_RETURN_ERROR(stream, "zero tag");
          }
        }

        if (!pb_field_iter_find(&iter, tag) || PB_LTYPE(iter.type) == PB_LTYPE_EXTENSION)
        {

            if (tag >= extension_range_start)
            {
                if (!find_extension_field(&iter))
                    extension_range_start = (uint32_t)-1;
                else
                    extension_range_start = iter.tag;

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


        if (PB_HTYPE(iter.type) == PB_HTYPE_REPEATED && iter.pSize == &iter.array_size)
        {
            if (fixed_count_field != iter.index) {


                if (fixed_count_field != PB_SIZE_MAX &&
                    fixed_count_size != fixed_count_total_size)
                {
                    PB_RETURN_ERROR(stream, "wrong size for fixed count field");
                }

                fixed_count_field = iter.index;
                fixed_count_size = 0;
                fixed_count_total_size = iter.array_size;
            }

            iter.pSize = &fixed_count_size;
        }

        if (PB_HTYPE(iter.type) == PB_HTYPE_REQUIRED
            && iter.required_field_index < PB_MAX_REQUIRED_FIELDS)
        {
            uint32_t tmp = ((uint32_t)1 << (iter.required_field_index & 31));
            fields_seen.bitfield[iter.required_field_index >> 5] |= tmp;
        }

        if (!decode_field(stream, wire_type, &iter))
            return false;
    }


    if (fixed_count_field != PB_SIZE_MAX &&
        fixed_count_size != fixed_count_total_size)
    {
        PB_RETURN_ERROR(stream, "wrong size for fixed count field");
    }


    {


        pb_size_t req_field_count;
        pb_type_t last_type;
        pb_size_t i;
        do {
            req_field_count = iter.required_field_index;
            last_type = iter.type;
        } while (pb_field_iter_next(&iter));


        if (PB_HTYPE(last_type) == PB_HTYPE_REQUIRED && iter.tag != 0)
            req_field_count++;

        if (req_field_count > PB_MAX_REQUIRED_FIELDS)
            req_field_count = PB_MAX_REQUIRED_FIELDS;

        if (req_field_count > 0)
        {

            for (i = 0; i < (req_field_count >> 5); i++)
            {
                if (fields_seen.bitfield[i] != allbits)
                    PB_RETURN_ERROR(stream, "missing required field");
            }


            if ((req_field_count & 31) != 0)
            {
                if (fields_seen.bitfield[req_field_count >> 5] !=
                    (allbits >> (uint_least8_t)(32 - (req_field_count & 31))))
                {
                    PB_RETURN_ERROR(stream, "missing required field");
                }
            }
        }
    }

    return true;
}
