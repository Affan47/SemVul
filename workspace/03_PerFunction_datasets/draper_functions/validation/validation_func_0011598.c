__enter_coll(uint64_t time,
	     enum coll_type_t type,
	     struct ezt_mpi_comm *comm,
	     int my_rank,
	     int len,
	     struct mpi_request* req,
	     char* thread_id)
{
  struct mpi_coll_msg_t* msg = __mpi_find_coll_message(type, comm, len, NULL, start_coll);

  if ( !msg) {
    msg = __new_coll_message(type, comm, len);
  }


  msg->comm[comm->my_rank] = comm;
  msg->times[comm->my_rank][start_coll] = time;
  msg->thread_ids[comm->my_rank] = thread_id;
  if(req) {
    msg->requests[comm->my_rank] = req;
    req->coll_msg = msg;
  }
  return msg;
}
