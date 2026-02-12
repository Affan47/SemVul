bool zmq::stream_engine_t::handshake ()
{
    zmq_assert (handshaking);
    zmq_assert (greeting_bytes_read < greeting_size);

    while (greeting_bytes_read < greeting_size) {
        const int n = tcp_read (s, greeting_recv + greeting_bytes_read,
                                greeting_size - greeting_bytes_read);
        if (n == 0) {
            error (connection_error);
            return false;
        }
        if (n == -1) {
            if (errno != EAGAIN)
                error (connection_error);
            return false;
        }

        greeting_bytes_read += n;


        if (greeting_recv [0] != 0xff)
            break;

        if (greeting_bytes_read < signature_size)
            continue;


        if (!(greeting_recv [9] & 0x01))
            break;


        if (outpos + outsize == greeting_send + signature_size) {
            if (outsize == 0)
                set_pollout (handle);
            outpos [outsize++] = 3;
        }

        if (greeting_bytes_read > signature_size) {
            if (outpos + outsize == greeting_send + signature_size + 1) {
                if (outsize == 0)
                    set_pollout (handle);


                if (greeting_recv [10] == ZMTP_1_0
                ||  greeting_recv [10] == ZMTP_2_0)
                    outpos [outsize++] = options.type;
                else {
                    outpos [outsize++] = 0;
                    memset (outpos + outsize, 0, 20);

                    zmq_assert (options.mechanism == ZMQ_NULL
                            ||  options.mechanism == ZMQ_PLAIN
                            ||  options.mechanism == ZMQ_CURVE
                            ||  options.mechanism == ZMQ_GSSAPI);

                    if (options.mechanism == ZMQ_NULL)
                        memcpy (outpos + outsize, "NULL", 4);
                    else
                    if (options.mechanism == ZMQ_PLAIN)
                        memcpy (outpos + outsize, "PLAIN", 5);
                    else
                    if (options.mechanism == ZMQ_GSSAPI)
                        memcpy (outpos + outsize, "GSSAPI", 6);
                    else
                    if (options.mechanism == ZMQ_CURVE)
                        memcpy (outpos + outsize, "CURVE", 5);
                    outsize += 20;
                    memset (outpos + outsize, 0, 32);
                    outsize += 32;
                    greeting_size = v3_greeting_size;
                }
            }
        }
    }


    const size_t revision_pos = 10;


    if (greeting_recv [0] != 0xff || !(greeting_recv [9] & 0x01)) {
        encoder = new (std::nothrow) v1_encoder_t (out_batch_size);
        alloc_assert (encoder);

        decoder = new (std::nothrow) v1_decoder_t (in_batch_size, options.maxmsgsize);
        alloc_assert (decoder);


        const size_t header_size = options.identity_size + 1 >= 255 ? 10 : 2;
        unsigned char tmp [10], *bufferp = tmp;


        const int rc = tx_msg.init_size (options.identity_size);
        zmq_assert (rc == 0);
        memcpy (tx_msg.data (), options.identity, options.identity_size);
        encoder->load_msg (&tx_msg);
        size_t buffer_size = encoder->encode (&bufferp, header_size);
        zmq_assert (buffer_size == header_size);


        inpos = greeting_recv;
        insize = greeting_bytes_read;


        if (options.type == ZMQ_PUB || options.type == ZMQ_XPUB)
            subscription_required = true;


        next_msg = &stream_engine_t::pull_msg_from_session;


        process_msg = &stream_engine_t::process_identity_msg;
    }
    else
    if (greeting_recv [revision_pos] == ZMTP_1_0) {
        encoder = new (std::nothrow) v1_encoder_t (
            out_batch_size);
        alloc_assert (encoder);

        decoder = new (std::nothrow) v1_decoder_t (
            in_batch_size, options.maxmsgsize);
        alloc_assert (decoder);
    }
    else
    if (greeting_recv [revision_pos] == ZMTP_2_0) {
        encoder = new (std::nothrow) v2_encoder_t (out_batch_size);
        alloc_assert (encoder);

        decoder = new (std::nothrow) v2_decoder_t (
            in_batch_size, options.maxmsgsize);
        alloc_assert (decoder);
    }
    else {
        encoder = new (std::nothrow) v2_encoder_t (out_batch_size);
        alloc_assert (encoder);

        decoder = new (std::nothrow) v2_decoder_t (
            in_batch_size, options.maxmsgsize);
        alloc_assert (decoder);

        if (options.mechanism == ZMQ_NULL
        &&  memcmp (greeting_recv + 12, "NULL\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 20) == 0) {
            mechanism = new (std::nothrow)
                null_mechanism_t (session, peer_address, options);
            alloc_assert (mechanism);
        }
        else
        if (options.mechanism == ZMQ_PLAIN
        &&  memcmp (greeting_recv + 12, "PLAIN\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 20) == 0) {
            if (options.as_server)
                mechanism = new (std::nothrow)
                    plain_server_t (session, peer_address, options);
            else
                mechanism = new (std::nothrow)
                    plain_client_t (options);
            alloc_assert (mechanism);
        }
#ifdef HAVE_LIBSODIUM
        else
        if (options.mechanism == ZMQ_CURVE
        &&  memcmp (greeting_recv + 12, "CURVE\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 20) == 0) {
            if (options.as_server)
                mechanism = new (std::nothrow)
                    curve_server_t (session, peer_address, options);
            else
                mechanism = new (std::nothrow) curve_client_t (options);
            alloc_assert (mechanism);
        }
#endif
#ifdef HAVE_LIBGSSAPI_KRB5
        else
        if (options.mechanism == ZMQ_GSSAPI
        &&  memcmp (greeting_recv + 12, "GSSAPI\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 20) == 0) {
            if (options.as_server)
                mechanism = new (std::nothrow)
                    gssapi_server_t (session, peer_address, options);
            else
                mechanism = new (std::nothrow) gssapi_client_t (options);
            alloc_assert (mechanism);
        }
#endif
        else {
            error (protocol_error);
            return false;
        }
        next_msg = &stream_engine_t::next_handshake_command;
        process_msg = &stream_engine_t::process_handshake_command;
    }


    if (outsize == 0)
        set_pollout (handle);


    handshaking = false;

    if (has_handshake_timer) {
        cancel_timer (handshake_timer_id);
        has_handshake_timer = false;
    }

    return true;
}
