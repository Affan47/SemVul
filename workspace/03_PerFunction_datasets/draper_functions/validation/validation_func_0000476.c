gnc_kvp_bag_find_by_guid (KvpFrame *root, const char * path,
                          const char *guid_name, const GncGUID *desired_guid)
{
    KvpValue *arr;
    KvpValueType valtype;
    GList *node;

    arr = kvp_frame_get_value (root, path);
    valtype = kvp_value_get_type (arr);
    if (KVP_TYPE_FRAME == valtype)
    {
        MATCH_GUID (arr);
        return NULL;
    }


    if (KVP_TYPE_GLIST != valtype) return NULL;

    for (node = kvp_value_get_glist(arr); node; node = node->next)
    {
        KvpValue *va = node->data;
        MATCH_GUID (va);
    }
    return NULL;
}
