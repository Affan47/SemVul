mca_pml_bfo_register_callbacks(void) {
    int rc;


    rc = mca_bml.bml_register( MCA_PML_BFO_HDR_TYPE_RNDVRESTARTNOTIFY,
                               mca_pml_bfo_recv_frag_callback_rndvrestartnotify,
                               NULL );
    if(OMPI_SUCCESS != rc)
        return rc;

    rc = mca_bml.bml_register( MCA_PML_BFO_HDR_TYPE_RNDVRESTARTACK,
                               mca_pml_bfo_recv_frag_callback_rndvrestartack,
                               NULL );
    if(OMPI_SUCCESS != rc)
        return rc;

    rc = mca_bml.bml_register( MCA_PML_BFO_HDR_TYPE_RNDVRESTARTNACK,
                               mca_pml_bfo_recv_frag_callback_rndvrestartnack,
                               NULL );
    if(OMPI_SUCCESS != rc)
        return rc;

    rc = mca_bml.bml_register( MCA_PML_BFO_HDR_TYPE_RECVERRNOTIFY,
                               mca_pml_bfo_recv_frag_callback_recverrnotify,
                               NULL );
    if(OMPI_SUCCESS != rc)
        return rc;

    return rc;
}
