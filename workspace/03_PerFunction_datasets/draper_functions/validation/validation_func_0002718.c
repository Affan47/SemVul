load_func(mca_bcol_base_module_t *super)
{
    int fnc;


    for (fnc = 0; fnc < BCOL_NUM_OF_FUNCTIONS; fnc++) {
        super->bcol_function_table[fnc] = NULL;
    }


#ifdef __PORTALS_AVAIL__
    super->bcol_function_table[BCOL_BCAST] = bcol_basesmuma_lmsg_scatter_allgather_portals_bcast;


#endif


    super->bcol_function_table[BCOL_BCAST]    =  bcol_basesmuma_bcast;
#ifdef __PORTALS_AVAIL__
    super->bcol_function_table[BCOL_BCAST] =
        bcol_basesmuma_lmsg_scatter_allgather_portals_bcast;
#endif

    super->bcol_function_table[BCOL_ALLREDUCE]  = bcol_basesmuma_allreduce_intra_recursive_doubling;
    super->bcol_function_table[BCOL_REDUCE]  = bcol_basesmuma_reduce_intra_fanin_old;

    super->bcol_memory_init                  = bcol_basesmuma_bank_init_opti;

    super->k_nomial_tree                     = bcol_basesmuma_setup_knomial_tree;


    super->set_small_msg_thresholds = bcol_basesmuma_set_small_msg_thresholds;
}
