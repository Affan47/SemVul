mca_coll_basic_reduce_scatter_block_intra(void *sbuf, void *rbuf, int rcount,
                                          struct ompi_datatype_t *dtype,
                                          struct ompi_op_t *op,
                                          struct ompi_communicator_t *comm,
                                          mca_coll_base_module_t *module)
{
    int rank, size, count, err = OMPI_SUCCESS;
    ptrdiff_t true_lb, true_extent, lb, extent, buf_size;
    char *recv_buf = NULL, *recv_buf_free = NULL;


    rank = ompi_comm_rank(comm);
    size = ompi_comm_size(comm);


    count = rcount * size;
    if (0 == count) {
        return OMPI_SUCCESS;
    }


    ompi_datatype_get_extent(dtype, &lb, &extent);
    ompi_datatype_get_true_extent(dtype, &true_lb, &true_extent);
    buf_size = true_extent + (count - 1) * extent;


    if (MPI_IN_PLACE == sbuf) {
        sbuf = rbuf;
    }

    if (0 == rank) {


        recv_buf_free = (char*) malloc(buf_size);
        recv_buf = recv_buf_free - lb;
        if (NULL == recv_buf_free) {
            err = OMPI_ERR_OUT_OF_RESOURCE;
            goto cleanup;
        }
    }


    err =
        comm->c_coll.coll_reduce(sbuf, recv_buf, count, dtype, op, 0,
                                 comm, comm->c_coll.coll_reduce_module);


    if (MPI_SUCCESS == err) {
        err = comm->c_coll.coll_scatter(recv_buf, rcount, dtype,
                                        rbuf, rcount, dtype, 0,
                                        comm, comm->c_coll.coll_scatter_module);
    }

 cleanup:
    if (NULL != recv_buf_free) free(recv_buf_free);

    return err;
}
