item_reload_icon(FmDirTreeModel* model, GList* item_l, GtkTreePath* tp)
{
    GtkTreeIter it;
    GList* l;
    FmDirTreeItem *item, *child;

    g_return_if_fail(item_l && tp);
    item = item_l->data;
    g_return_if_fail(item);

    if(item->icon)
    {
        g_object_unref(item->icon);
        item->icon = NULL;
        item_to_tree_iter(model, item_l, &it);
        gtk_tree_model_row_changed(GTK_TREE_MODEL(model), tp, &it);
    }

    if(item->children)
    {
        gtk_tree_path_append_index(tp, 0);
        for(l = item->children; l; l=l->next)
        {
            child = (FmDirTreeItem*)l->data;
            item_reload_icon(model, l, tp);
            gtk_tree_path_next(tp);
        }
        gtk_tree_path_up(tp);
    }

    for(l = item->hidden_children; l; l=l->next)
    {
        child = (FmDirTreeItem*)l->data;
        if(child->icon)
        {
            g_object_unref(child->icon);
            child->icon = NULL;
        }
    }
}
