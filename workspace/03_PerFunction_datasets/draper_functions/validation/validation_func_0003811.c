z_ucs_output(z_ucs *z_ucs_output)
{
  TRACE_LOG("Output: \"");
  TRACE_LOG_Z_UCS(z_ucs_output);
  TRACE_LOG("Output: \"");
  TRACE_LOG("\" to window %d, buffering: %d.\n",
      active_z_window_id,
      active_z_window_id != -1 ? z_windows[active_z_window_id]->buffering : -1);

  if (active_z_window_id == -1)
    screen_cell_interface->z_ucs_output(z_ucs_output);
  else
  {
    if (bool_equal(z_windows[active_z_window_id]->buffering, false))
    {
      update_output_colours(active_z_window_id);
      update_output_text_style(active_z_window_id);

      z_ucs_output_window_target(
          z_ucs_output,
          (void*)(&z_windows[active_z_window_id]->window_number));
    }
    else
    {
      wordwrap_wrap_z_ucs(
        z_windows[active_z_window_id]->wordwrapper, z_ucs_output);
    }
  }
  TRACE_LOG("z_ucs_output finished.\n");
}
