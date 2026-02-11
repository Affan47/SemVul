MPI_Accumulate(CONST void* origin_addr, VT_MPI_INT origin_count,
                          MPI_Datatype origin_datatype, VT_MPI_INT target_rank,
                          MPI_Aint target_disp, VT_MPI_INT target_count,
                          MPI_Datatype target_datatype, MPI_Op op,
                          MPI_Win win)
{
  VT_MPI_INT result;
  uint32_t tid;

  GET_THREAD_ID(tid);

  if (IS_MPI_TRACE_ON(tid))
    {
      uint64_t time;
      uint8_t was_recorded;

      MPI_TRACE_OFF(tid);

      time = vt_pform_wtime();
      was_recorded = vt_enter(tid, &time, vt_mpi_regid[VT__MPI_ACCUMULATE]);

      VT_UNIMCI_CHECK_PRE(MPI_Accumulate,
        (origin_addr, origin_count, origin_datatype, target_rank, target_disp,
         target_count, target_datatype, op, win, "", 0, 0),
         was_recorded, &time);

      result = PMPI_Accumulate(origin_addr, origin_count, origin_datatype,
                               target_rank, target_disp, target_count,
                               target_datatype, op, win);

      VT_UNIMCI_CHECK_POST(MPI_Accumulate,
        (origin_addr, origin_count, origin_datatype, target_rank, target_disp,
         target_count, target_datatype, op, win, "", 0, 0),
         was_recorded, &time);

#if defined(HAVE_MPI2_THREAD) && HAVE_MPI2_THREAD
      if (!is_mpi_multithreaded)
#endif
        {
          if (target_rank != MPI_PROC_NULL &&
              (was_recorded || env_mpi_ignore_filter))
            {
              MPI_Comm comm;
              VT_MPI_INT sz;
              uint32_t gid, wid;

              PMPI_Type_size(origin_datatype, &sz);
              vt_win_id(win, &comm, &gid, &wid);
              if (is_rma_putre)
                vt_mpi_rma_putre(tid, &time, VT_RANK_TO_PE(target_rank, comm),
                                 gid, wid, sz * origin_count );
              else
                vt_mpi_rma_put(tid, &time, VT_RANK_TO_PE(target_rank, comm),
                               gid, wid, sz * origin_count );
            }
        }

      time = vt_pform_wtime();
      vt_exit(tid, &time);

      MPI_TRACE_ON(tid);
    }
  else
    {
      result = PMPI_Accumulate(origin_addr, origin_count, origin_datatype,
                               target_rank, target_disp, target_count,
                               target_datatype, op, win);
    }

  return result;
}
