void zmq::stream_engine_t::restart_output ()
{
    if (unlikely (io_error))
        return;

    if (likely (output_stopped)) {
        set_pollout (handle);
        output_stopped = false;
    }


    out_event ();
}
