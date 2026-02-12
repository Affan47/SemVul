int zmq::stream_engine_t::write_subscription_msg (msg_t *msg_)
{
    msg_t subscription;


    int rc = subscription.init_size (1);
    errno_assert (rc == 0);
    *(unsigned char*) subscription.data () = 1;
    rc = session->push_msg (&subscription);
    if (rc == -1)
       return -1;

    process_msg = &stream_engine_t::push_msg_to_session;
    return push_msg_to_session (msg_);
}
