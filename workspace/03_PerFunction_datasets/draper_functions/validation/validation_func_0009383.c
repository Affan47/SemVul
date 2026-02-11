menu_paste (void)
{
  struct Bond *tmp;

  if (is_drawing)
  {
    cancel_action ();
    return;
  }

  tmp = copy_selection (copy_buffer, 1000, -1000);
  if (bonds == NULL)
  {
    bonds = copy_buffer;
    num_sel = num_sel_recompute (bonds);
  }
  else
    concat_bond_lists (bonds, copy_buffer, &num_sel);

  copy_buffer = tmp;
  advance_undo (_("paste"));
  REDRAW;
}
