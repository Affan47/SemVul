tree_rm(struct pathx *p) {
    struct tree *tree, **del;
    int cnt = 0, ndel = 0, i;

    for (tree = pathx_first(p); tree != NULL; tree = pathx_next(p)) {
        if (! TREE_HIDDEN(tree))
            ndel += 1;
    }

    if (ndel == 0)
        return 0;

    if (ALLOC_N(del, ndel) < 0) {
        free(del);
        return -1;
    }

    for (i = 0, tree = pathx_first(p); tree != NULL; tree = pathx_next(p)) {
        if (TREE_HIDDEN(tree))
            continue;
        pathx_symtab_remove_descendants(pathx_get_symtab(p), tree);
        del[i] = tree;
        i += 1;
    }

    for (i = 0; i < ndel; i++)
        cnt += tree_unlink_raw(del[i]);
    free(del);

    return cnt;
}
