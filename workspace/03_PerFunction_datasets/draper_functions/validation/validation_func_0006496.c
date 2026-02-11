free_allreduce_offsets_array(mca_bcol_ptpcoll_module_t *ptpcoll_module)
{
    int rc = OMPI_SUCCESS, i = 0;
    netpatterns_k_exchange_node_t *k_node = &ptpcoll_module->knomial_exchange_tree;
    int n_exchanges = k_node->n_exchanges;

    if (ptpcoll_module->allgather_offsets) {
        for (i=0; i < n_exchanges; i++) {
            free (ptpcoll_module->allgather_offsets[i]);
        }
    }

    free(ptpcoll_module->allgather_offsets);
    ptpcoll_module->allgather_offsets = NULL;
    return rc;
}
