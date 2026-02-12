void zmq::stream_engine_t::timer_event (int id_)
{
    zmq_assert (id_ == handshake_timer_id);
    has_handshake_timer = false;


    error (timeout_error);
}
