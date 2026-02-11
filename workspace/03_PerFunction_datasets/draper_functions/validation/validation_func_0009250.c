init_array_pred_succ(DtScheInfo *dt_sche)
{
    int amax, bmax, i;

    amax = get_max_array_entry(dt_sche->block[1]->module->array_head);
    bmax = get_max_block_no(dt_sche->block[1]);
    dt_sche->array_pred = (IntSet **)calloc(bmax + 1, sizeof(IntSet *));
    dt_sche->array_succ = (IntSet **)calloc(bmax + 1, sizeof(IntSet *));
    if (dt_sche->array_pred == NULL
        || dt_sche->array_succ == NULL)
        fatal("No room for pred/succ.\n");

    for (i = 1; i < bmax + 1; i++) {
        dt_sche->array_pred[i] = construct_IntSet_array(amax + 1, bmax + 1);
        dt_sche->array_succ[i] = construct_IntSet_array(amax + 1, bmax + 1);
    }
    make_all_array_pred_succ_intset(dt_sche->block[1],
                                    dt_sche->array_pred,
                                    dt_sche->array_succ);
}
