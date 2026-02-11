vt_plugin_cntr_write_post_mortem(VTThrd * thrd) {
  uint32_t counter_index;
  uint64_t * counter_current_indices;
  vt_plugin_cntr_timevalue ** time_values_by_counter = NULL;
  uint32_t number_of_counters;
  uint64_t * number_of_values_by_counter;
  uint64_t dummy_time;
  uint32_t tid;
  struct vt_plugin_single_counter current_counter;
  struct vt_plugin_cntr_defines * plugin_cntr_defines =
      (struct vt_plugin_cntr_defines *) thrd->plugin_cntr_defines;
  if (plugin_cntr_defines == NULL)
    return;

  if (plugin_cntr_defines->size_of_counters[VT_PLUGIN_CNTR_ASYNCH_POST_MORTEM]
      == 0)
    return;
  if (VTTHRD_TRACE_STATUS(thrd) != VT_TRACE_ON)
    return;
  for (tid=0;tid<VTThrdn;tid++)
    if ( VTThrdv[tid] == thrd )
      break;
  if ( tid == VTThrdn ){
    vt_warning("Can not determine internal TID when gathering post-mortem counters");
    return;
  }

  number_of_counters
    = plugin_cntr_defines->size_of_counters[VT_PLUGIN_CNTR_ASYNCH_POST_MORTEM];
  dummy_time = vt_pform_wtime();


  thrd->plugin_cntr_writing_post_mortem = 1;


  time_values_by_counter = calloc(number_of_counters, sizeof(*time_values_by_counter));
  vt_libassert(time_values_by_counter);
  number_of_values_by_counter = calloc(number_of_counters, sizeof(*number_of_values_by_counter));
  vt_libassert(number_of_values_by_counter);
  for (counter_index = 0;
       counter_index < number_of_counters;
       counter_index++) {
    current_counter
        = plugin_cntr_defines->counters[VT_PLUGIN_CNTR_ASYNCH_POST_MORTEM][counter_index];

    number_of_values_by_counter[counter_index] = current_counter.getAllValues(
        current_counter.from_plugin_id, &(time_values_by_counter[counter_index]));
    if (time_values_by_counter[counter_index] == NULL) {
      free(time_values_by_counter);
      free(number_of_values_by_counter);
      return;
    }
  }

  counter_current_indices = calloc(number_of_counters, sizeof(*counter_current_indices));
  vt_libassert(counter_current_indices);
  while (1) {
	vt_plugin_cntr_timevalue *min_tvp = NULL;
	uint32_t min_counter;
    for (counter_index = 0;
	     counter_index < number_of_counters;
	     counter_index++)
    {


	  vt_plugin_cntr_timevalue *tvp;
	  if (counter_current_indices[counter_index] >= number_of_values_by_counter[counter_index]) {
		continue;
	  }
	  tvp = &(time_values_by_counter[counter_index][counter_current_indices[counter_index]]);
      if (!min_tvp || tvp->timestamp < min_tvp->timestamp) {
        min_tvp = tvp;
        min_counter = counter_index;
      }
	}
    if (min_tvp == NULL) {

      break;
    }
    current_counter
        = plugin_cntr_defines->counters[VT_PLUGIN_CNTR_ASYNCH_POST_MORTEM][min_counter];
    WRITE_ASYNCH_DATA(thrd, tid, current_counter, *min_tvp, &dummy_time);
    counter_current_indices[min_counter]++;
  }
  free(time_values_by_counter);
  free(counter_current_indices);
  free(number_of_values_by_counter);

  thrd->plugin_cntr_writing_post_mortem = 0;
}
