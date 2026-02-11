col_delete_collection(struct collection_item *ci,
                                  col_item_cleanup_fn cb,
                                  void *custom_data)
{
    TRACE_FLOW_STRING("col_delete_collection", "Entry.");

    if (ci == NULL) {
        TRACE_FLOW_STRING("col_delete_collection", "Nothing to do Exit.");
        return;
    }

    TRACE_INFO_STRING("Real work to do", "");
    TRACE_INFO_STRING("Property", ci->property);
    TRACE_INFO_NUMBER("Next item", ci->next);

    col_delete_collection(ci->next, cb, custom_data);


    col_delete_item_with_cb(ci, cb, custom_data);
    TRACE_FLOW_STRING("col_delete_collection", "Exit.");
}
