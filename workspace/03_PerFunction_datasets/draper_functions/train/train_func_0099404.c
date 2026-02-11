tree_full_name(tree_t* tree)
{
    char* res;

    if (tree->parent)
    {
        char* p = tree_full_name(tree->parent);
        res = g_strdup_printf("%s/%s", p, tree->name);
        g_free(p);
    }
    else
    {
        res = g_strdup(tree->name);
    }

    return res;
}
