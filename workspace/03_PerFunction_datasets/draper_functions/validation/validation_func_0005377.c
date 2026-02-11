ibus_engine_desc_parse_xml_node (IBusEngineDesc *desc,
                                XMLNode       *node)
{
    GList *p;

    for (p = node->sub_nodes; p != NULL; p = p->next) {
        XMLNode *sub_node = (XMLNode *) p->data;

#define PARSE_ENTRY(field_name, element_name)                   \
        if (g_strcmp0 (sub_node->name, element_name) == 0) {    \
            g_free (desc->priv->field_name);                    \
            desc->priv->field_name = g_strdup (sub_node->text); \
            continue;                                           \
        }
#define PARSE_ENTRY_1(name) PARSE_ENTRY(name, #name)
        PARSE_ENTRY_1(name);
        PARSE_ENTRY_1(longname);
        PARSE_ENTRY_1(description);
        PARSE_ENTRY_1(language);
        PARSE_ENTRY_1(license);
        PARSE_ENTRY_1(author);
        PARSE_ENTRY_1(icon);
        PARSE_ENTRY_1(layout);
        PARSE_ENTRY_1(layout_variant);
        PARSE_ENTRY_1(layout_option);
        PARSE_ENTRY_1(hotkeys);
        PARSE_ENTRY_1(symbol);
        PARSE_ENTRY_1(setup);
        PARSE_ENTRY_1(version);
        PARSE_ENTRY_1(textdomain);
#undef PARSE_ENTRY
#undef PARSE_ENTRY_1
        if (g_strcmp0 (sub_node->name , "rank") == 0) {
            desc->priv->rank = atoi (sub_node->text);
            continue;
        }
        g_warning ("<engines> element contains invalidate element <%s>", sub_node->name);
    }
    return TRUE;
}
