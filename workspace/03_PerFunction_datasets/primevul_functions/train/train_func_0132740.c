void zmq::stream_engine_t::out_event ()
{
    zmq_assert (!io_error);


    if (!outsize) {


        if (unlikely (encoder == NULL)) {
            zmq_assert (handshaking);
            return;
        }

        outpos = NULL;
        outsize = encoder->encode (&outpos, 0);

        while (outsize < out_batch_size) {
            if ((this->*next_msg) (&tx_msg) == -1)
                break;
            encoder->load_msg (&tx_msg);
            unsigned char *bufptr = outpos + outsize;
            size_t n = encoder->encode (&bufptr, out_batch_size - outsize);
            zmq_assert (n > 0);
            if (outpos == NULL)
                outpos = bufptr;
            outsize += n;
        }


        if (outsize == 0) {
            output_stopped = true;
            reset_pollout (handle);
            return;
        }
    }


    const int nbytes = tcp_write (s, outpos, outsize);


    if (nbytes == -1) {
        reset_pollout (handle);
        return;
    }

    outpos += nbytes;
    outsize -= nbytes;


    if (unlikely (handshaking))
        if (outsize == 0)
            reset_pollout (handle);
}
