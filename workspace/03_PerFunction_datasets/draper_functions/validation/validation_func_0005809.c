InsertTree(TreeNode node, Color color, int depth)
{
    int index;

    if (! node)
    {
        node = GetTreeNode();
        if (! node)
            goto error;

        node->r    = 0;
        node->g    = 0;
        node->b    = 0;
        node->knt  = 0;
        node->leaf = depth == 7;

        if (! node->leaf)
        {
            node->next = depthlist[depth].next;
            depthlist[depth].next = node;
            depthlist[depth].knt ++;
        }

        if (node->leaf)
            nLeaves ++;
    }

    if (node->leaf)
    {
        node->r += color->r;
        node->g += color->g;
        node->b += color->b;
    }
    else
    {
        BRANCH(color, depth, index);
        node->kids[index] =
                InsertTree(node->kids[index], color, depth+1);
        if (! node->kids[index])
            goto error;
    }

    node->knt ++;

    return node;

error:
    return NULL;
}
