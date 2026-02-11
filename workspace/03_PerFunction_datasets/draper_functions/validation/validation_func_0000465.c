vt_exit(uint32_t tid, uint64_t* time)
{
  uint8_t do_trace;

  GET_THREAD_ID(tid);


  if (VTTHRD_TRACE_STATUS(VTThrdv[tid]) == VT_TRACE_OFF_PERMANENT) return;


  do_trace = !((VTTHRD_TRACE_STATUS(VTThrdv[tid]) == VT_TRACE_OFF) ||
               (VTTHRD_STACK_LEVEL(VTThrdv[tid]) > max_stack_depth));


  VTTHRD_STACK_POP(VTThrdv[tid]);

#if !defined(VT_DISABLE_RFG)
  if (do_trace && have_filter_spec)
  {


    if (VTTHRD_RECFILT_ENABLED(VTThrdv[tid]) &&
        VTTHRD_STACK_LEVEL(VTThrdv[tid]) >=
        VTTHRD_STACK_LEVEL_AT_RECFILT_ENABLED(VTThrdv[tid]))
    {
      do_trace = 0;
    }

    else
    {


      if (!RFG_Regions_stackPop(VTTHRD_RFGREGIONS(VTThrdv[tid]),
                                NULL, NULL, &do_trace))
      {
        vt_libassert(0);
      }


      if (!do_trace)
      {


        if (VTTHRD_RECFILT_ENABLED(VTThrdv[tid]))
          VTTHRD_STACK_LEVEL_AT_RECFILT_ENABLED(VTThrdv[tid]) = -1;
      }
    }
  }
#endif

  if (do_trace)
  {

    update_counter(tid, time);
    if (VTTHRD_TRACE_STATUS(VTThrdv[tid]) != VT_TRACE_ON) return;


    VTGen_write_LEAVE(VTTHRD_GEN(VTThrdv[tid]), time, 0, 0);
  }
}
