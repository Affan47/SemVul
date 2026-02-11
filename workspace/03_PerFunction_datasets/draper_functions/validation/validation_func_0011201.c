us_http_server_handler_dispatch( us_http_server_handler_t *self )
{
    bool r = false;
    us_buffer_t *incoming = &self->m_base.m_incoming_queue;
    us_buffer_t *outgoing = &self->m_base.m_outgoing_queue;
    us_log_tracepoint();
    if ( self->m_director->dispatch(
             self->m_director, self->m_request_header, incoming, self->m_response_header, self->m_response_content ) >= 0 )
    {
        r = us_http_response_header_flatten( self->m_response_header, outgoing );
        if ( r )
        {

            if ( strcmp( self->m_request_header->m_method, "HEAD" ) != 0 )
            {
                if ( us_buffer_writable_count( outgoing ) > us_buffer_readable_count( self->m_response_content ) )
                {
                    us_buffer_write_buffer( outgoing, self->m_response_content );
                    us_http_server_handler_set_state_sending_response( self );

                    r = true;
                    us_log_debug( "response header and content ready" );
                }
                else
                {
                    r = false;
                    us_log_error( "unable to buffer http response content" );
                }
            }
            else
            {
                us_http_server_handler_set_state_sending_response( self );
                r = true;
            }
        }
        else
        {
            us_log_error( "unable to flatten response header" );
        }
    }
    if ( !r )
    {
        self->m_base.close( &self->m_base );
    }
    return r;
}
