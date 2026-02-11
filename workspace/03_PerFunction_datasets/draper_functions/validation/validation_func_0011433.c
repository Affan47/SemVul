us_osc_msg_bundle_flatten( const us_osc_msg_bundle_t *self, us_buffer_t *buf, int32_t *total_length )
{
    bool r = true;
    us_osc_msg_t *cur = 0;
    int32_t start_length = (int32_t)us_buffer_readable_count( buf );
    r &= us_buffer_append_data( buf, "#bundle", 8 );
    r &= us_buffer_append_uint64( buf, self->m_timetag_high, self->m_timetag_low );
    cur = self->m_first_msg;
    if ( !cur )
    {

        r &= us_buffer_append_int32( buf, 0 );
    }
    else
    {
        int32_t msg_size = 0;
        int32_t last_msg_size_pos = 0;
        while ( cur && r )
        {

            last_msg_size_pos = (int32_t)us_buffer_in_position( buf );

            r &= us_buffer_append_int32( buf, 0 );
            r &= cur->flatten( cur, buf, &msg_size );

            us_buffer_poke_uint32( buf, last_msg_size_pos, msg_size );

            cur = cur->m_next;
        }
    }

    r &= us_buffer_append_int32( buf, 0 );

    if ( total_length )
    {
        *total_length = (int32_t)us_buffer_readable_count( buf ) - start_length;
    }
    return r;
}
