void zmq::stream_engine_t::mechanism_ready ()
{
    if (options.recv_identity) {
        msg_t identity;
        mechanism->peer_identity (&identity);
        const int rc = session->push_msg (&identity);
        if (rc == -1 && errno == EAGAIN) {


            return;
        }
        errno_assert (rc == 0);
        session->flush ();
    }

    next_msg = &stream_engine_t::pull_and_encode;
    process_msg = &stream_engine_t::write_credential;


    typedef metadata_t::dict_t properties_t;
    properties_t properties;
    properties_t::const_iterator it;


    const properties_t& zap_properties = mechanism->get_zap_properties ();
    it = zap_properties.begin ();
    while (it != zap_properties.end ()) {
        properties.insert (properties_t::value_type (it->first, it->second));
        it++;
    }


    const properties_t& zmtp_properties = mechanism->get_zmtp_properties ();
    it = zmtp_properties.begin ();
    while (it != zmtp_properties.end ()) {
        properties.insert (properties_t::value_type (it->first, it->second));
        it++;
    }

    zmq_assert (metadata == NULL);
    if (!properties.empty ())
        metadata = new (std::nothrow) metadata_t (properties);
}
