void zmq::stream_engine_t::plug (io_thread_t *io_thread_,
    session_base_t *session_)
{
    zmq_assert (!plugged);
    plugged = true;


    zmq_assert (!session);
    zmq_assert (session_);
    session = session_;
    socket = session-> get_socket ();


    io_object_t::plug (io_thread_);
    handle = add_fd (s);
    io_error = false;

    if (options.raw_sock) {

        encoder = new (std::nothrow) raw_encoder_t (out_batch_size);
        alloc_assert (encoder);

        decoder = new (std::nothrow) raw_decoder_t (in_batch_size);
        alloc_assert (decoder);


        handshaking = false;

        next_msg = &stream_engine_t::pull_msg_from_session;
        process_msg = &stream_engine_t::push_msg_to_session;


        msg_t connector;
        connector.init();
        push_msg_to_session (&connector);
        connector.close();
        session->flush ();
    }
    else {

        set_handshake_timer ();


        outpos = greeting_send;
        outpos [outsize++] = 0xff;
        put_uint64 (&outpos [outsize], options.identity_size + 1);
        outsize += 8;
        outpos [outsize++] = 0x7f;
    }

    set_pollin (handle);
    set_pollout (handle);

    in_event ();
}
