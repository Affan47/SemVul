o_grips_size(GSCHEM_TOPLEVEL *w_current)
{
  TOPLEVEL *toplevel = w_current->toplevel;
  int factor, size;

  factor = (int) toplevel->page_current->to_world_x_constant;
  if (factor > SMALL_ZOOMFACTOR1) {

    size = SCREENabs (w_current, GRIP_SIZE1);
  } else if (factor > SMALL_ZOOMFACTOR2) {

    size = SCREENabs (w_current, GRIP_SIZE2);
  } else {

    size = SCREENabs (w_current, GRIP_SIZE3);
  }

  return min(size, MAXIMUM_GRIP_PIXELS/2);
}
