xattach_pipes (reader_t *inpipe_, writer_t *outpipe_,
    const blob_t &peer_identity_)
{
    zmq_assert (!inpipe && !outpipe);

    inpipe = inpipe_;
    inpipe_alive = true;
    inpipe->set_event_sink (this);

    outpipe = outpipe_;
    outpipe_alive = true;
    outpipe->set_event_sink (this);

    if (terminating) {
        register_term_acks (2);
        inpipe_->terminate ();
        outpipe_->terminate ();
    }
}
