frag_send_cb (ompi_request_t *request)
{
    ompi_osc_rdma_frag_t *frag =
        (ompi_osc_rdma_frag_t*) request->req_complete_cb_data;
    ompi_osc_rdma_module_t *module = frag->module;

    OPAL_OUTPUT_VERBOSE((50, ompi_osc_base_framework.framework_output,
                         "osc rdma: frag_send complete to %d, frag = %p, request = %p",
                         frag->target, (void *) frag, (void *) request));

    mark_outgoing_completion(module);
    OPAL_FREE_LIST_RETURN(&mca_osc_rdma_component.frags, &frag->super);


    osc_rdma_gc_add_request (request);

    return OMPI_SUCCESS;
}
