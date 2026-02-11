apply_filter (GUPnPDIDLLiteWriter *writer,
              const char          *filter,
              gboolean             tags_only)
{
        char **tokens;
        GList *allowed = NULL;
        unsigned short i;
        xmlNode *node;

        g_return_if_fail (GUPNP_IS_DIDL_LITE_WRITER (writer));
        g_return_if_fail (filter != NULL);

        if (filter[0] == '*') {

                xmlNewNs (writer->priv->xml_node,
                          writer->priv->dlna_ns->href,
                          writer->priv->dlna_ns->prefix);
                return;
        }

        tokens = g_strsplit (filter, ",", -1);
        g_return_if_fail (tokens != NULL);

        for (i = 0; tokens[i] != NULL; i++)
                allowed = g_list_append (allowed, tokens[i]);

        for (node = writer->priv->xml_node->children;
             node != NULL;
             node = node->next)
                filter_node (node, allowed, writer, tags_only);

        if (writer->priv->dlna_attr_present) {
                xmlNewNs (writer->priv->xml_node,
                          writer->priv->dlna_ns->href,
                          writer->priv->dlna_ns->prefix);
        }

        g_list_free (allowed);
        g_strfreev (tokens);
}
