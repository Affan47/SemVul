remove_chars_from_history(OUTPUTHISTORY *history, int nof_chars)
{
  z_ucs *ptr = history->z_history_buffer_front_index;
  bool has_wrapped = history->wrapped_around;
  z_ucs last_data = 0;

  TRACE_LOG("Removing %d chars from history at %p.\n", nof_chars, ptr);

  while (nof_chars > 0)
  {
    if ((ptr = decrement_buffer_pointer(history, ptr, &has_wrapped)) == NULL)

      return -1;

    if ( (*ptr == HISTORY_METADATA_ESCAPE) && (last_data != 0) )
    {
      nof_chars += (last_data = HISTORY_METADATA_TYPE_COLOUR ? 4 : 3);
    }
    else
    {
      last_data = *ptr;
      nof_chars --;
    }
  }

  history->z_history_buffer_front_index = ptr;
  history->wrapped_around = has_wrapped;

  TRACE_LOG("History went to %p.\n", ptr);

  return 0;
}
