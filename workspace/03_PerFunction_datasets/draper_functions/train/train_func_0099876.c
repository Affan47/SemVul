calc_dt_gain(Stasche *sinfo, const int pcno, const int mtno)
{
    Array_def_use_table_semnode *gain = NULL;
    Array_table *ahead = sinfo->module->array_head;
    int **sched = sinfo->sched;
    int *ntasks = sinfo->ntasks;
    real gain_size = 0, next_size = 0;
    int i;

    for (i = ntasks[pcno] - 1; i >= sinfo->onlmtasks[pcno]; i--) {
        int prev_mt = sched[pcno][i];
        Array_def_use_table_semnode *fd, *id = NULL;
        IntSet local_array = NULL;
        if (flg_lad_ya_templ) {
            if (sinfo->block[prev_mt]->cmp_localize != NULL) {
                local_array = sinfo->block[prev_mt]->cmp_localize->local_array;
                fd = copy_array_def_use_table_semnode(
                    get_array_def_use(sinfo->block[prev_mt], sinfo->block[mtno]));
                fd = select_array_du_semnode(fd, local_array, NULL, NULL);
                id = copy_array_def_use_table_semnode(
                    get_array_use_use(sinfo->block[prev_mt], sinfo->block[mtno]));
                id = select_array_du_semnode(id, local_array, NULL, NULL);
            } else {
                fd = NULL;
                id = NULL;
            }
        } else {
            fd = get_array_def_use(sinfo->block[prev_mt], sinfo->block[mtno]);
            id = get_array_use_use(sinfo->block[prev_mt], sinfo->block[mtno]);
        }
        gain = union_array_def_use_table_semnode(sinfo->module,
                                                 gain,
                                                 fd);
        gain = union_array_def_use_table_semnode(sinfo->module,
                                                 gain,
                                                 id);
        if (flg_lad_ya_templ) {
            free_all_array_def_use_table_semnode(fd);
            free_all_array_def_use_table_semnode(id);
        }
        gain_size = next_size;
        next_size = get_max_array_du_semnode_size(gain, ahead);
        if (next_size > (lm_size + dsm_size) / 4) {
            break;
        } else {
            gain_size = next_size;
        }
    }

    free_all_array_def_use_table_semnode(gain);

    return gain_size;
}
