init_invoke_table(mca_coll_ml_module_t *ml_module)
{
    int i=0,j=0,k=0, index_topo;
    int bcoll_type;
    struct mca_bcol_base_module_t *bcol_module = NULL;
    int j_bcol_module=0;
    int i_hier=0;
    mca_coll_ml_topology_t *topo;

    for (index_topo = 0; index_topo < COLL_ML_TOPO_MAX; index_topo++) {
        topo = &ml_module->topo_list[index_topo];
        if (COLL_ML_TOPO_DISABLED == topo->status) {

            continue;
        }
        for (i_hier = 0; i_hier < topo->n_levels; i_hier++) {

            for (j_bcol_module = 0;
                    j_bcol_module < topo->component_pairs[i_hier].num_bcol_modules;
                    ++j_bcol_module) {

                bcol_module = topo->component_pairs[i_hier].bcol_modules[j_bcol_module];

                for (bcoll_type = 0; bcoll_type < BCOL_NUM_OF_FUNCTIONS ; bcoll_type++){
                    for (i=0; i<NUM_MSG_RANGES; i++) {
                        for (j=0; j<OMPI_OP_NUM_OF_TYPES; j++) {
                            for (k=0; k<OMPI_DATATYPE_MAX_PREDEFINED; k++) {
                                bcol_module->filtered_fns_table[DATA_SRC_UNKNOWN][BLOCKING][bcoll_type][i][j][k]
                                    = NULL;

                                bcol_module->filtered_fns_table[DATA_SRC_KNOWN][BLOCKING][bcoll_type][i][j][k]
                                    = NULL;

                                bcol_module->filtered_fns_table[DATA_SRC_UNKNOWN][NON_BLOCKING][bcoll_type][i][j][k]
                                    = NULL;

                                bcol_module->filtered_fns_table[DATA_SRC_KNOWN][NON_BLOCKING][bcoll_type][i][j][k]
                                    = NULL;

                            }
                        }
                    }
                }
            }

        }
    }

    return 0;
}
