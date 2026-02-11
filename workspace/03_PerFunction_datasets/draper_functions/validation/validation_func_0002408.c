o_buffer_cut(GSCHEM_TOPLEVEL *w_current, int buf_num)
{
  if (buf_num < 0 || buf_num >= MAX_BUFFERS) {
    g_warning (_("o_buffer_cut: Invalid buffer %i\n"), buf_num);
    return;
  }

  selection_to_buffer (w_current, buf_num);
  o_delete_selected(w_current);
}
