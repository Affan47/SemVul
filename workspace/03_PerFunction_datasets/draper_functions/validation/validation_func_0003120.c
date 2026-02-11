AlignmentView_destroy(AlignmentView *av){
    register gint i;
    for(i = 0; i < av->split_codon_separation_list->len; i++)
        g_free(av->split_codon_separation_list->pdata[i]);
    g_ptr_array_free(av->split_codon_separation_list, TRUE);
    g_string_free(av->outer_query,  TRUE);
    g_string_free(av->middle, TRUE);
    g_string_free(av->outer_target,  TRUE);

    if(av->inner_query)
        g_string_free(av->inner_query, TRUE);
    if(av->inner_target)
        g_string_free(av->inner_target, TRUE);

    for(i = 0; i < av->row_marker->len; i++)
        g_free(av->row_marker->pdata[i]);
    g_ptr_array_free(av->row_marker, TRUE);
    g_free(av);
    return;
    }
