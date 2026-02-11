mtn_sdn_has_child(Slapi_DN *target_sdn)
{
    mapping_tree_node *node;


    node = slapi_get_mapping_tree_node_by_dn(target_sdn);


    if (node == NULL)
        return 0;

    node = node->mtn_children;
    while (node)
    {
        if (slapi_sdn_issuffix(node->mtn_subtree, target_sdn))
            return 1;
        node = node->mtn_brother;
    }
    return 0;
}
