test_planner(int rank)
{


     int i, dim;
     int r, s;
     rfftwnd_mpi_plan pnd[PLANNER_TEST_SIZE];
     int *narr, maxdim;

     chk_mem_leak = 0;
     verbose--;

     please_wait();
     if (rank < 2)
          rank = 2;

     narr = (int *) fftw_malloc(rank * sizeof(int));

     for (i = 0; i < PLANNER_TEST_SIZE; ++i) {
          pnd[i] = (rfftwnd_mpi_plan) 0;
     }

     maxdim = (int) pow(8192, 1.0/rank);

     for (i = 0; i < PLANNER_TEST_SIZE * PLANNER_TEST_SIZE; ++i) {
          r = rand();
          if (r < 0)
               r = -r;
          r = r % PLANNER_TEST_SIZE;

          for (dim = 0; dim < rank; ++dim) {
               do {
                    s = rand();
                    if (s < 0)
                         s = -s;
                    s = s % maxdim + 1;
               } while (s == 0);
               narr[dim] = s;
          }

	  if (rank > 1) {
	       if (pnd[r])
		    rfftwnd_mpi_destroy_plan(pnd[r]);

	       pnd[r] = rfftwnd_mpi_create_plan(MPI_COMM_WORLD, rank, narr,
					       random_dir(), measure_flag |
					       wisdom_flag);
	  }

          if (i % (PLANNER_TEST_SIZE * PLANNER_TEST_SIZE / 20) == 0) {
               WHEN_VERBOSE(0, my_printf("test planner: so far so good\n"));
               WHEN_VERBOSE(0, my_printf("test planner: iteration %d"
					 " out of %d\n",
                              i, PLANNER_TEST_SIZE * PLANNER_TEST_SIZE));
          }
     }

     for (i = 0; i < PLANNER_TEST_SIZE; ++i) {
          if (pnd[i])
               rfftwnd_mpi_destroy_plan(pnd[i]);
     }

     fftw_free(narr);
     verbose++;
     chk_mem_leak = 1;
}
