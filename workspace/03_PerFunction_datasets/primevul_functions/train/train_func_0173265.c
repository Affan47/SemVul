void Jsi_TreeDelete (Jsi_Tree *treePtr)
{
    SIGASSERTV(treePtr, TREE);
    if (treePtr->flags.destroyed)
        return;

    treePtr->flags.destroyed = 1;
    destroy_node(treePtr->opts.interp, treePtr->root);
    _JSI_MEMCLEAR(treePtr);
    Jsi_Free(treePtr);
}
