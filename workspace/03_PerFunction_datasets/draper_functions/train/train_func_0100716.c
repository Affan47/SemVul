decide_some_prefetch_mt_between_dlg(Info_for_prefetch *info_p,
                                    int use_mt,
                                    int assigns,
                                    int *assign,
                                    real *TaskEndTime,
                                    real *clock,
                                    int pre_dlg_no,
                                    Array_def_use_table *cache_state,
                                    IntSet *some_mt)
{
    int i;
    Array_def_use_table *du;
    IntSet intset_mt;

    for (du = cache_state; du != NULL; du = du->next) {
        int entry = du->entry;
        intset_mt = some_mt[entry];

        for (i = assigns - 1; i >= 0; i--) {
            int in_mt = assign[i];

            if (info_p->mt_data[in_mt]->dlg_tag == pre_dlg_no
                && info_p->mt_data[in_mt]->LoopNest
                == info_p->mt_data[use_mt]->LoopNest
                && is_similar_loop(info_p->mt_data[in_mt]->loop_data,
                                   info_p->mt_data[use_mt]->loop_data)) {
                if (TaskEndTime[in_mt] > clock[entry])
                    add1_IntSet(intset_mt, in_mt);
            }
        }
    }
}
