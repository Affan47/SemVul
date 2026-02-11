mca_coll_basic_neighbor_alltoallw_graph(const void *sbuf, const int scounts[], const MPI_Aint sdisps[],
                                        struct ompi_datatype_t * const sdtypes[], void *rbuf, const int rcounts[],
                                        const MPI_Aint rdisps[], struct ompi_datatype_t * const rdtypes[],
                                        struct ompi_communicator_t *comm, mca_coll_base_module_t *module)
{
    mca_coll_basic_module_t *basic_module = (mca_coll_basic_module_t *) module;
    const mca_topo_base_comm_graph_2_1_0_t *graph = comm->c_topo->mtc.graph;
    int rc = MPI_SUCCESS, neighbor, degree;
    const int rank = ompi_comm_rank (comm);
    ompi_request_t **reqs;
    const int *edges;

    mca_topo_base_graph_neighbors_count (comm, rank, &degree);

    edges = graph->edges;
    if (rank > 0) {
        edges += graph->index[rank - 1];
    }


    for (neighbor = 0, reqs = basic_module->mccb_reqs ; neighbor < degree ; ++neighbor) {
        rc = MCA_PML_CALL(irecv((char *) rbuf + rdisps[neighbor], rcounts[neighbor], rdtypes[neighbor],
                                edges[neighbor], MCA_COLL_BASE_TAG_ALLTOALL, comm, reqs++));
        if (OMPI_SUCCESS != rc) break;
    }

    if (OMPI_SUCCESS != rc) {

        return rc;
    }

    for (neighbor = 0 ; neighbor < degree ; ++neighbor) {

        rc = MCA_PML_CALL(isend((char *) sbuf + sdisps[neighbor], scounts[neighbor], sdtypes[neighbor],
                                edges[neighbor], MCA_COLL_BASE_TAG_ALLTOALL, MCA_PML_BASE_SEND_STANDARD,
                                comm, reqs++));
        if (OMPI_SUCCESS != rc) break;
    }

    if (OMPI_SUCCESS != rc) {

        return rc;
    }

    return ompi_request_wait_all (degree * 2, basic_module->mccb_reqs, MPI_STATUSES_IGNORE);
}
