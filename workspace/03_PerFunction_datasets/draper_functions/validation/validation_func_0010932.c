edit_match_calc_func(gint query_pos, gint target_pos,
                                     gpointer user_data){
    register EditDistance_Data *edd = (EditDistance_Data*)user_data;
    g_assert(query_pos >= 0);
    g_assert(target_pos >= 0);
    g_assert(query_pos < edd->query_len);
    g_assert(target_pos < edd->target_len);
    if(edd->query[query_pos] == edd->target[target_pos])
         return 0;
    else
         return -1;
    }
