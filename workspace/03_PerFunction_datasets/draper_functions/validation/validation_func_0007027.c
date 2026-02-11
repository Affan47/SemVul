append_actions (GUPnPServiceProxy         *proxy,
                GUPnPServiceIntrospection *introspection,
                const GList               *actions,
                GtkTreeStore              *store,
                GtkTreeIter               *service_iter)
{
        const GList *iter;

        for (iter = actions; iter; iter = iter->next) {
                GUPnPServiceActionInfo *info;
                GtkTreeIter             action_iter;

                info = iter->data;

                gtk_tree_store_insert_with_values
                                (store, &action_iter,
                                 service_iter, -1,
                                 0, get_icon_by_id (ICON_ACTION),
                                 1, info->name,
                                 2, proxy,
                                 3, introspection,
                                 4, info,
                                 5, ICON_ACTION,
                                 -1);
                append_action_arguments (info->arguments,
                                         store,
                                         &action_iter);
        }
}
