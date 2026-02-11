xmpp_stream_get_roster(XmppStream *stream)
{
    xmlnode   *node;
    IqRequest *iq;

    g_return_if_fail(stream != NULL);

    xmpp_stream_iqid_increase(stream);

    iq = iq_request_create(stream, IQ_TYPE_GET);
    iq_request_set_callback(iq, request_roster_cb, NULL);

    node = xmlnode_new_child(iq->node, "query");
    xmlnode_new_namespace(node, NULL, NS_IQ_ROSTER);

#if 0
    xmlnode_new_namespace(node, "gr", NS_GOOGLE_ROSTER);
    xmlnode_new_prop(node, "gr:ext", "2");
#endif

    if (iq_request_send(iq) != HYBRID_OK) {

        hybrid_account_error_reason(stream->account->account,
                                    _("request roster error."));
        iq_request_destroy(iq);

        return;
    }

    iq_request_destroy(iq);
}
