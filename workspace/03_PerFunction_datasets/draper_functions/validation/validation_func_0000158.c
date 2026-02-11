send_mssg(struct mssg_t *mssg_ptr,
	  hbool_t add_req_to_tag)
{
    const char * fcn_name = "send_mssg()";
    hbool_t success = TRUE;
    int mssg_tag = CACHE_TEST_TAG;
    int result;
    static long mssg_num = 0;

    if ( ( mssg_ptr == NULL ) ||
         ( mssg_ptr->src != world_mpi_rank ) ||
         ( mssg_ptr->dest < 0 ) ||
         ( mssg_ptr->dest == mssg_ptr->src ) ||
         ( mssg_ptr->dest >= world_mpi_size ) ||
         ( mssg_ptr->req < 0 ) ||
         ( mssg_ptr->req > MAX_REQ_CODE ) ||
         ( mssg_ptr->magic != MSSG_MAGIC ) ) {

        nerrors++;
        success = FALSE;
        if ( verbose ) {
            HDfprintf(stdout, "%d:%s: Invalid mssg on entry.\n",
                      world_mpi_rank, fcn_name);
        }
    }

    if ( success ) {

        mssg_ptr->mssg_num = mssg_num++;

	if ( add_req_to_tag ) {

	    mssg_tag += mssg_ptr->req;
	}

        result = MPI_Send((void *)mssg_ptr, 1, mpi_mssg_t,
                          mssg_ptr->dest, mssg_tag, world_mpi_comm);

        if ( result != MPI_SUCCESS ) {

            nerrors++;
            success = FALSE;
            if ( verbose ) {
                HDfprintf(stdout, "%d:%s: MPI_Send() failed.\n",
                          world_mpi_rank, fcn_name);
            }
        }
    }

    return(success);

}
