slapi_be_select( const Slapi_DN *sdn )
{
    Slapi_Backend *be;
    mapping_tree_node *node= slapi_get_mapping_tree_node_by_dn(sdn);
    if((node!=NULL) && (node->mtn_be!=NULL))
        be= node->mtn_be[0];
    else
        be = NULL;

    if(be==NULL)
        be= defbackend_get_backend();

    return be;
}
