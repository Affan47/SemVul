get_child_by_name (xmlrpc_env *env, xml_element *parent, char *name)
{
    size_t child_count, i;
    xml_element **children;

    children = xml_element_children(parent);
    child_count = xml_element_children_size(parent);
    for (i = 0; i < child_count; i++) {
        if (0 == strcmp(xml_element_name(children[i]), name))
            return children[i];
    }

    xmlrpc_env_set_fault_formatted(env, XMLRPC_PARSE_ERROR,
                                   "Expected <%s> to have child <%s>",
                                   xml_element_name(parent), name);
    return NULL;
}
