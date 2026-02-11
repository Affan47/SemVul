fc_xchg_alloc_iob ( struct fc_exchange *xchg,
					      size_t len ) {
	struct fc_port *port = xchg->port;
	struct io_buffer *iobuf;

	iobuf = xfer_alloc_iob ( &port->transport,
				 ( sizeof ( struct fc_frame_header ) + len ) );
	if ( iobuf ) {
		iob_reserve ( iobuf, sizeof ( struct fc_frame_header ) );
	}
	return iobuf;
}
