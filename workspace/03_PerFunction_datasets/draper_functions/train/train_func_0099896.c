draw_mesh_grid_region (GSCHEM_TOPLEVEL *w_current,
                                   int x, int y, int width, int height)
{
  int x_start, y_start, x_end, y_end;
  int incr;
  int screen_incr;

  incr = w_current->snap_size;
  screen_incr = SCREENabs (w_current, incr);

  SCREENtoWORLD (w_current, x - 1, y + height + 1, &x_start, &y_start);
  SCREENtoWORLD (w_current, x + width + 1, y - 1, &x_end, &y_end);


  if (screen_incr >= w_current->mesh_grid_display_threshold) {
    draw_mesh (w_current, MESH_GRID_MINOR_COLOR, x_start, y_start,
               x_end, y_end, incr, MESH_COARSE_GRID_MULTIPLIER);
  }

  incr *= MESH_COARSE_GRID_MULTIPLIER;
  screen_incr = SCREENabs (w_current, incr);


  if (screen_incr >= w_current->mesh_grid_display_threshold) {
    draw_mesh (w_current, MESH_GRID_MAJOR_COLOR,
               x_start, y_start, x_end, y_end, incr, 0);
  }
}
