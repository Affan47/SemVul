find_recurring_actions(GListPtr input, node_t * not_on_node)
{
    const char *value = NULL;
    GListPtr result = NULL;
    GListPtr gIter = input;

    CRM_CHECK(input != NULL, return NULL);

    for (; gIter != NULL; gIter = gIter->next) {
        action_t *action = (action_t *) gIter->data;

        value = g_hash_table_lookup(action->meta, XML_LRM_ATTR_INTERVAL);
        if (value == NULL) {

        } else if (safe_str_eq(value, "0")) {

        } else if (safe_str_eq(CRMD_ACTION_CANCEL, action->task)) {

        } else if (not_on_node == NULL) {
            crm_trace("(null) Found: %s", action->uuid);
            result = g_list_prepend(result, action);

        } else if (action->node == NULL) {

        } else if (action->node->details != not_on_node->details) {
            crm_trace("Found: %s", action->uuid);
            result = g_list_prepend(result, action);
        }
    }

    return result;
}
