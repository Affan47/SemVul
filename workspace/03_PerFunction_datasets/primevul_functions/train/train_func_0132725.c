void zmq::stream_engine_t::in_event ()
{
    zmq_assert (!io_error);


    if (unlikely (handshaking))
        if (!handshake ())
            return;

    zmq_assert (decoder);


    if (input_stopped) {
        rm_fd (handle);
        io_error = true;
        return;
    }


    if (!insize) {


        size_t bufsize = 0;
        decoder->get_buffer (&inpos, &bufsize);

        const int rc = tcp_read (s, inpos, bufsize);
        if (rc == 0) {
            error (connection_error);
            return;
        }
        if (rc == -1) {
            if (errno != EAGAIN)
                error (connection_error);
            return;
        }


        insize = static_cast <size_t> (rc);
    }

    int rc = 0;
    size_t processed = 0;

    while (insize > 0) {
        rc = decoder->decode (inpos, insize, processed);
        zmq_assert (processed <= insize);
        inpos += processed;
        insize -= processed;
        if (rc == 0 || rc == -1)
            break;
        rc = (this->*process_msg) (decoder->msg ());
        if (rc == -1)
            break;
    }


    if (rc == -1) {
        if (errno != EAGAIN) {
            error (protocol_error);
            return;
        }
        input_stopped = true;
        reset_pollin (handle);
    }

    session->flush ();
}
