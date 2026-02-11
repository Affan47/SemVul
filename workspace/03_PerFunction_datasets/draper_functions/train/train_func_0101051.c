plist_get_node_type(plist_t node)
{
    if (node)
    {
        plist_data_t data = plist_get_data(node);
        if (data)
            return data->type;
    }
    return PLIST_NONE;
}
