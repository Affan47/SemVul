set_av_transport_uri_cb (GUPnPService       *service,
                         GUPnPServiceAction *action,
                         BognorAvTransport  *transport)
{
    BognorAvTransportPrivate *priv = transport->priv;
    struct _set_av_transport_uri_data data;
    GUPnPDIDLLiteParser *parser;
    char *uri, *metadata;
    GError *error = NULL;

    if (check_instance_id (action) == FALSE) {
        return;
    }

    gupnp_service_action_get (action,
                              "CurrentURI", G_TYPE_STRING, &uri,
                              "CurrentURIMetaData", G_TYPE_STRING, &metadata,
                              NULL);
    g_print ("Uri: %s\nMetadata: %s\n", uri, metadata);

    data.transport = transport;
    data.action = action;
    data.uri = uri;
    data.metadata = metadata;

    parser = gupnp_didl_lite_parser_new ();
    g_signal_connect (parser, "object-available",
                      G_CALLBACK (set_av_transport_object_avail_cb), &data);
    gupnp_didl_lite_parser_parse_didl (parser, metadata, &error);
    if (error != NULL) {
        g_warning ("Error parsing DIDL: %s\n", metadata);
        g_error_free (error);
        g_free (uri);
        g_free (metadata);

        gupnp_service_action_return_error (action, 714, "Illegal MIME type");
        return;
    }

    g_free (uri);
    g_free (metadata);
}
