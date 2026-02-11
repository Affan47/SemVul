vt_mpi_rma_put(uint32_t tid, uint64_t* time, uint32_t tpid, uint32_t cid,
                    uint32_t tag, uint64_t sent)
{
  GET_THREAD_ID(tid);

  if (VTTHRD_TRACE_STATUS(VTThrdv[tid]) != VT_TRACE_ON) return;

  VTGen_write_RMA_PUT(VTTHRD_GEN(VTThrdv[tid]),
                      time,
                      VT_PROCESS_ID(vt_my_trace, tid),
                      tpid+1,
                      cid,
                      tag,
                      sent,
                      0);
}
