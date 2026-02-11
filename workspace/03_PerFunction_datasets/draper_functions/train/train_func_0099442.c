lam_ssi_coll_lam_basic_allreduce(void *sbuf, void *rbuf, int count,
				 MPI_Datatype dtype, MPI_Op op,
				 MPI_Comm comm)
{
  int err;


  err = comm->c_ssi_coll.lsca_reduce(sbuf, rbuf, count, dtype,
				     op, 0, comm);
  if (err != MPI_SUCCESS)
    return err;

  return comm->c_ssi_coll.lsca_bcast(rbuf, count, dtype, 0, comm);
}
