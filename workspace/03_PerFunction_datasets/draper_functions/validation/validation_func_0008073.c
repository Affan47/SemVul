bcol_ptpcoll_barrier_extra_node_progress(
                            bcol_function_args_t *input_args,
                            struct coll_ml_function_t *const_args)
{

    ompi_request_t **requests;
    int rc, completed, num_reqs = 2;

    mca_bcol_ptpcoll_collreq_t *collreq =
                    (mca_bcol_ptpcoll_collreq_t *) input_args->bcol_opaque_data;

    requests = collreq->requests;


    completed =
        mca_bcol_ptpcoll_test_all_for_match(&num_reqs, requests, &rc);
    if (OPAL_UNLIKELY(OMPI_SUCCESS != rc)) {
        PTPCOLL_ERROR(("Test for all failed."));
        return rc;
    }

    if (!completed) {
        return BCOL_FN_STARTED;
    }

    return BCOL_FN_COMPLETE;
}
