ario_conf_save (G_GNUC_UNUSED gpointer data)
{
        ARIO_LOG_FUNCTION_START;
        xmlNodePtr cur;
        xmlDocPtr doc;
        char *xml_filename;

        if (!modified)
                return TRUE;
        modified = FALSE;

        doc = xmlNewDoc (XML_VERSION);
        cur = xmlNewNode (NULL, (const xmlChar *) XML_ROOT_NAME);
        xmlDocSetRootElement (doc, cur);

        g_hash_table_foreach (hash,
                              (GHFunc) ario_conf_save_foreach,
                              cur);

        xml_filename = g_build_filename (ario_util_config_dir (), "options.xml", NULL);


        xmlSaveFormatFile (xml_filename, doc, TRUE);

        g_free (xml_filename);
        xmlFreeDoc (doc);

        return TRUE;
}
