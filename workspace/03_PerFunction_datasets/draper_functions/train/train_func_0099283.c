eight_byte_size_ready ()
{


    size_t size = (size_t) get_uint64 (tmpbuf);


    int rc = zmq_msg_init_size (&in_progress, size);
    errno_assert (rc == 0);

    next_step (zmq_msg_data (&in_progress), size,
        &zmq_decoder_t::message_ready);
    return true;
}
