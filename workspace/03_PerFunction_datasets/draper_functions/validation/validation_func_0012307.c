btree_successor(ompi_rb_tree_t * tree, ompi_rb_tree_node_t * node)
{
    ompi_rb_tree_node_t * p;

    if (node->right == tree->nill) {
        p = node->parent;
        while (node == p->right) {
            node = p;
            p = p->parent;
        }
        if(p == tree->root_ptr) {
            return(tree->nill);
        }
        return p;
    }

    p = node->right;
    while(p->left != tree->nill) {
        p = p->left;
    }
    return p;
}
