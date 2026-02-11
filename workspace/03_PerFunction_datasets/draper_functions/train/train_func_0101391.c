vt_plugin_cntr_write_callback_data(uint64_t *time, uint32_t tid) {
  uint32_t i, k;
  struct vt_plugin_single_counter * current_counter;
  vt_plugin_cntr_timevalue * values;
  struct vt_plugin_cntr_defines * plugin_cntr_defines =
      (struct vt_plugin_cntr_defines *) VTThrdv[tid]->plugin_cntr_defines;

  if (plugin_cntr_defines == NULL)
    return;
  if (plugin_cntr_defines->size_of_counters[VT_PLUGIN_CNTR_ASYNCH_CALLBACK]
      == 0)
    return;
  for (i = 0;
    i < plugin_cntr_defines->size_of_counters[VT_PLUGIN_CNTR_ASYNCH_CALLBACK];
    i++) {
    current_counter
        = &plugin_cntr_defines->counters[VT_PLUGIN_CNTR_ASYNCH_CALLBACK][i];
#if (defined(VT_MT) || defined (VT_HYB) || defined(VT_JAVA))
    VTThrd_lock((VTThrdMutex **) &(current_counter->callback_mutex));
#endif
    values = current_counter->callback_values;
    for (k = 0; k < current_counter->current_callback_write_position; k++) {
      WRITE_ASYNCH_DATA(VTThrdv[tid], tid, (*current_counter), values[k], time);
    }
    current_counter->current_callback_write_position = 0;
#if (defined(VT_MT) || defined (VT_HYB) || defined(VT_JAVA))
    VTThrd_unlock((VTThrdMutex **) &(current_counter->callback_mutex));
#endif
  }
}
