Scheduler_Pair_reset_rows(Scheduler_Pair *spair){
    register gint i;
    register Scheduler_Row *row;
    for(i = 0; i <= spair->row_index->max_advance; i++){
        row = Lookahead_get(spair->row_index, i);
        if(row){
            g_assert(Scheduler_Row_is_valid(row));
            Scheduler_Row_reset(row);
            }
        }
    return;
    }
