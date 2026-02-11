setup_func(xmlNodePtr node)
{
    xmlNodePtr n;
    Options *o;

    o = g_slice_new0(Options);

    if ((n = obt_xml_find_node(node, "command")) ||
        (n = obt_xml_find_node(node, "execute")))
    {
        gchar *s = obt_xml_node_string(n);
        o->cmd = obt_paths_expand_tilde(s);
        g_free(s);
    }
    return o;
}
