void zmq::stream_engine_t::unplug ()
{
    zmq_assert (plugged);
    plugged = false;


    if (has_handshake_timer) {
        cancel_timer (handshake_timer_id);
        has_handshake_timer = false;
    }


    if (!io_error)
        rm_fd (handle);


    io_object_t::unplug ();

    session = NULL;
}
