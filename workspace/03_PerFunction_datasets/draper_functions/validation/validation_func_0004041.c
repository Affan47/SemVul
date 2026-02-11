fli_handle_timeouts( long * msec )
{
    FLI_TIMEOUT_REC *rec,
                    *next;
    long sec = 0,
         usec,
         elapsed,
         diff;

    if ( ! fli_context->timeout_rec )
        return;

    fl_gettime( &sec, &usec );


    for ( rec = fli_context->timeout_rec; rec; rec = next )
    {
        next = rec->next;

        elapsed =   1000 * ( sec - rec->start_sec )
                  + ( usec - rec->start_usec ) / 1000;
        diff = rec->ms_to_wait - elapsed;

        if ( diff <= 0 )
        {
            if ( rec->callback )
            {
                rec->callback( rec->id, rec->data );
                fl_gettime( &sec, &usec );
            }

            remove_timeout( rec );
        }
        else
            *msec = FL_min( *msec, diff );
    }
}
