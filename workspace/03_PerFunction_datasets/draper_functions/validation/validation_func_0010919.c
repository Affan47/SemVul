us_reactor_create_tcp_client( us_reactor_t *self,
                                   us_allocator_t *allocator,
                                   void *extra,
                                   ssize_t queue_buf_size,
                                   const char *server_host,
                                   const char *server_port,
                                   bool keep_open,
                                   us_reactor_handler_create_proc_t client_handler_create,
                                   us_reactor_handler_tcp_client_init_proc_t client_handler_init )
{
    bool r = false;
    us_reactor_handler_tcp_client_t *handler = (us_reactor_handler_tcp_client_t *)client_handler_create( allocator );
    if ( handler )
    {
        r = client_handler_init(
            &handler->m_base.m_base, allocator, -1, extra, queue_buf_size, server_host, server_port, keep_open );
        if ( r )
        {
            r = self->add_item( self, &handler->m_base.m_base );
        }
    }
    return r;
}
