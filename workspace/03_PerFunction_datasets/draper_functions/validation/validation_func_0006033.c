ompi_coll_tuned_reduce_scatter_intra_dec_fixed( void *sbuf, void *rbuf,
                                                    int *rcounts,
                                                    struct ompi_datatype_t *dtype,
                                                    struct ompi_op_t *op,
                                                    struct ompi_communicator_t *comm,
                                                    mca_coll_base_module_t *module)
{
    int comm_size, i, pow2;
    size_t total_message_size, dsize;
    const double a = 0.0012;
    const double b = 8.0;
    const size_t small_message_size = 12 * 1024;
    const size_t large_message_size = 256 * 1024;

    OPAL_OUTPUT((ompi_coll_tuned_stream, "ompi_coll_tuned_reduce_scatter_intra_dec_fixed"));

    comm_size = ompi_comm_size(comm);

    ompi_datatype_type_size(dtype, &dsize);
    total_message_size = 0;
    for (i = 0; i < comm_size; i++) {
        total_message_size += rcounts[i];
    }

    if( !ompi_op_is_commute(op) ) {
        return ompi_coll_tuned_reduce_scatter_intra_nonoverlapping (sbuf, rbuf, rcounts,
                                                                    dtype, op,
                                                                    comm, module);
    }

    total_message_size *= dsize;


    pow2 = opal_next_poweroftwo_inclusive (comm_size);

    if ((total_message_size <= small_message_size) ||
        ((total_message_size <= large_message_size) && (pow2 == comm_size)) ||
        (comm_size >= a * total_message_size + b)) {
        return
            ompi_coll_tuned_reduce_scatter_intra_basic_recursivehalving(sbuf, rbuf, rcounts,
                                                                        dtype, op,
                                                                        comm, module);
    }
    return ompi_coll_tuned_reduce_scatter_intra_ring(sbuf, rbuf, rcounts,
                                                     dtype, op,
                                                     comm, module);
}
