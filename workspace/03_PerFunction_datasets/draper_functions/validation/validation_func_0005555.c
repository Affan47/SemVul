mca_btl_tcp_endpoint_recv_connect_ack(mca_btl_base_endpoint_t* btl_endpoint)
{
    ompi_process_name_t guid;
    size_t s;
    mca_btl_tcp_proc_t* btl_proc = btl_endpoint->endpoint_proc;

    s = mca_btl_tcp_endpoint_recv_blocking(btl_endpoint,
                                           &guid, sizeof(ompi_process_name_t));
    if (s != sizeof(ompi_process_name_t)) {
        if (0 == s) {


            return OMPI_ERROR;
        }
	opal_show_help("help-mpi-btl-tcp.txt", "client handshake fail",
                       true, ompi_process_info.nodename,
                       ompi_process_info.pid,
                       "did not receive entire connect ACK from peer");
        return OMPI_ERR_UNREACH;
    }
    OMPI_PROCESS_NAME_NTOH(guid);

    if (OPAL_EQUAL != ompi_rte_compare_name_fields(OMPI_RTE_CMP_ALL,
                                                    &btl_proc->proc_ompi->proc_name,
                                                    &guid)) {
        BTL_ERROR(("received unexpected process identifier %s",
                   OMPI_NAME_PRINT(&guid)));
        mca_btl_tcp_endpoint_close(btl_endpoint);
        return OMPI_ERR_UNREACH;
    }

    return OMPI_SUCCESS;
}
