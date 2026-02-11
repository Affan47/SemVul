rect2grid (void)
{
  grid.x1 = (rect.x1 - drgrid->xoffset) / env.grid_dx;
  grid.y1 = (rect.y1 - drgrid->yoffset) / env.grid_dy;

  grid.x2 = (rect.x2 - drgrid->xoffset) / env.grid_dx;
  grid.y2 = (rect.y2 - drgrid->yoffset) / env.grid_dy;

  if (((rect.x2 - drgrid->xoffset) % env.grid_dx) != 0) grid.x2 += 1;
  if (((rect.y2 - drgrid->yoffset) % env.grid_dy) != 0) grid.y2 += 1;

  if (    (grid.x2 < 0) || (grid.x1 >= drgrid->X)
       || (grid.y2 < 0) || (grid.y1 >= drgrid->Y) ) {
    grid.x1 = -1;
  } else {
    if (grid.x1 < 0          ) grid.x1 = 0;
    if (grid.y1 < 0          ) grid.y1 = 0;
    if (grid.x2 > drgrid->X-1) grid.x2 = drgrid->X - 1;
    if (grid.y2 > drgrid->Y-1) grid.y2 = drgrid->Y - 1;
  }
}
