gnc_book_end_handler(gpointer data_for_children,
                     GSList* data_from_children, GSList* sibling_data,
                     gpointer parent_data, gpointer global_data,
                     gpointer *result, const gchar *tag)
{
    xmlNodePtr tree = (xmlNodePtr)data_for_children;
    gxpf_data *gdata = (gxpf_data*)global_data;
    QofBook *book = gdata->bookdata;


    if (parent_data) return TRUE;


    if (!tag) return TRUE;

    g_return_val_if_fail(tree, FALSE);

    book = dom_tree_to_book(tree, book);
    if (!book)
        gdata->cb(tag, gdata->parsedata, book);

    xmlFreeNode(tree);

    return book != NULL;
}
