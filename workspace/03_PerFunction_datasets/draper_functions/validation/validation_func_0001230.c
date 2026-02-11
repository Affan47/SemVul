rmaps_lama_prune_max_tree(opal_tree_t *max_tree, opal_tree_item_t *parent_item)
{
    int ret;
    opal_tree_item_t *child_item = NULL, *next_item;
    int i;
    bool found;
    rmaps_lama_level_type_t *key_max;
    char *tmp_str = NULL;


    if( NULL == parent_item ) {
        return ORTE_SUCCESS;
    }


    child_item  = opal_tree_get_first_child(parent_item);
    while( child_item != NULL ) {


        next_item  = opal_tree_get_next_sibling(child_item);

        if( ORTE_SUCCESS != (ret = rmaps_lama_prune_max_tree(max_tree,
                                                             child_item)) ) {
            return ret;
        }

        child_item = next_item;
    }

    key_max = (rmaps_lama_level_type_t*)max_tree->get_key(parent_item);


    found = false;
    for(i = 0; i < lama_mapping_num_layouts; ++i ) {
        if( 0 == max_tree->comp(parent_item, &lama_mapping_layout[i]) ) {
            found = true;
            break;
        }
    }

    if( !found ) {
        if( 15 <= opal_output_get_verbosity(orte_rmaps_base_framework.framework_output) ) {
            tmp_str = lama_type_enum_to_str(*key_max);
            opal_output_verbose(5, orte_rmaps_base_framework.framework_output,
                                "mca:rmaps:lama: ----- Before pruning %s",
                                tmp_str);
            free(tmp_str);
            rmaps_lama_max_tree_pretty_print_tree(max_tree);
        }

        opal_tree_remove_item(max_tree, parent_item);

        return ORTE_SUCCESS;
    }

    return ORTE_SUCCESS;
}
