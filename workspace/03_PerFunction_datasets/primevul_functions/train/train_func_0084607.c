void page_collection_unlock(struct page_collection *set)
{

    g_tree_destroy(set->tree);
    g_free(set);
}
