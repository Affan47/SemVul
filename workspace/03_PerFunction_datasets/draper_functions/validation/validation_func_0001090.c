set_up_file_communicator(void)
{
    const char * fcn_name = "set_up_file_communicator()";
    hbool_t success = TRUE;
    int mpi_result;
    int num_excluded_ranks;
    int excluded_ranks[1];
    MPI_Group file_group;
    MPI_Group world_group;

    if ( success ) {

        mpi_result = MPI_Comm_group(world_mpi_comm, &world_group);

        if ( mpi_result != MPI_SUCCESS ) {

            nerrors++;
            success = FALSE;
	    if ( verbose ) {
                fprintf(stdout,
                        "%d:%s: MPI_Comm_group() failed with error %d.\n",
                        world_mpi_rank, fcn_name, mpi_result);
            }
        }
    }

    if ( success ) {

        num_excluded_ranks = 1;
        excluded_ranks[0] = world_server_mpi_rank;
        mpi_result = MPI_Group_excl(world_group, num_excluded_ranks,
                                    excluded_ranks, &file_group);

        if ( mpi_result != MPI_SUCCESS ) {

            nerrors++;
            success = FALSE;
            if ( verbose ) {
                fprintf(stdout,
                        "%d:%s: MPI_Group_excl() failed with error %d.\n",
                        world_mpi_rank, fcn_name, mpi_result);
            }
        }
    }

    if ( success ) {

        mpi_result = MPI_Comm_create(world_mpi_comm, file_group,
                                     &file_mpi_comm);

        if ( mpi_result != MPI_SUCCESS ) {

            nerrors++;
            success = FALSE;
            if ( verbose ) {
                fprintf(stdout,
                        "%d:%s: MPI_Comm_create() failed with error %d.\n",
                        world_mpi_rank, fcn_name, mpi_result);
            }

        } else {

            if ( world_mpi_rank != world_server_mpi_rank ) {

                if ( file_mpi_comm == MPI_COMM_NULL ) {

                    nerrors++;
                    success = FALSE;
                    if ( verbose ) {
                        fprintf(stdout,
                                "%d:%s: file_mpi_comm == MPI_COMM_NULL.\n",
                                world_mpi_rank, fcn_name);
                    }
                }
            } else {

                file_mpi_size = world_mpi_size - 1;

                if ( file_mpi_comm != MPI_COMM_NULL ) {

                    nerrors++;
                    success = FALSE;
                    if ( verbose ) {
                        fprintf(stdout,
                                "%d:%s: file_mpi_comm != MPI_COMM_NULL.\n",
                                world_mpi_rank, fcn_name);
                    }
                }
            }
        }
    }

    if ( ( success ) && ( world_mpi_rank != world_server_mpi_rank ) ) {

        mpi_result = MPI_Comm_size(file_mpi_comm, &file_mpi_size);

        if ( mpi_result != MPI_SUCCESS ) {

            nerrors++;
            success = FALSE;
            if ( verbose ) {
                fprintf(stdout,
                        "%d:%s: MPI_Comm_size() failed with error %d.\n",
                        world_mpi_rank, fcn_name, mpi_result);
            }
        }
    }

    if ( ( success ) && ( world_mpi_rank != world_server_mpi_rank ) ) {

        mpi_result = MPI_Comm_rank(file_mpi_comm, &file_mpi_rank);

        if ( mpi_result != MPI_SUCCESS ) {

            nerrors++;
            success = FALSE;
            if ( verbose ) {
                fprintf(stdout,
                        "%d:%s: MPI_Comm_rank() failed with error %d.\n",
                        world_mpi_rank, fcn_name, mpi_result);
            }
        }
    }

    return(success);

}
