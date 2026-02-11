us_reactor_handler_udp_init_ex( us_reactor_handler_t *self_,
                                     us_allocator_t *allocator,
                                     void *extra,
                                     const char *ethernet_port,
                                     struct addrinfo *localaddr,
                                     struct addrinfo *multicastaddr,
                                     size_t input_packets,
                                     size_t output_packets,
                                     size_t max_packet_size )
{
    bool r = false;
    int fd;
    us_reactor_handler_udp_t *self = (us_reactor_handler_udp_t *)self_;

    self->m_incoming_packets = 0;
    self->m_outgoing_packets = 0;
    self->tick = 0;
    self->queue_readable = us_reactor_handler_udp_queue_readable;
    self->packet_received = 0;
    fd = us_net_create_multicast_tx_udp_socket( localaddr, multicastaddr, ethernet_port );
    if ( fd >= 0 )
    {
        r = us_reactor_handler_init( self_, allocator, fd, extra );
        self_->tick = us_reactor_handler_udp_tick;
        self_->destroy = us_reactor_handler_udp_destroy;
        self_->readable = us_reactor_handler_udp_readable;
        self_->writable = us_reactor_handler_udp_writable;
        if ( r )
        {
            self->m_incoming_packets = us_packet_queue_create( allocator, input_packets, max_packet_size );
            self->m_outgoing_packets = us_packet_queue_create( allocator, output_packets, max_packet_size );
            self_->m_wake_on_readable = true;
            self_->m_wake_on_writable = false;
        }
    }
    if ( !r )
    {
        us_reactor_handler_udp_destroy( self_ );
    }
    return r;
}
