resize_manager(WinManager *man, int force)
{
  ManGeometry *new;
  int oldwidth, oldheight, oldrows, oldcols, old_boxwidth, old_boxheight;
  int dir;
  int i;

  if (man->flags.is_shaded)
  {
    man->flags.needs_resize_after_unshade = 1;
    return;
  }
  if (man->can_draw == 0)
    return;

  oldwidth = man->geometry.width;
  oldheight = man->geometry.height;
  oldrows = man->geometry.rows;
  oldcols = man->geometry.cols;
  dir = man->geometry.dir;
  old_boxwidth = man->geometry.boxheight;
  old_boxheight = man->geometry.boxwidth;

  if (dir & GROW_FIXED) {
    new = figure_geometry(man);
    set_man_geometry(man, new);
    set_shape(man);
    if (force || oldrows != new->rows || oldcols != new->cols ||
	oldwidth != new->width || oldheight != new->height) {
      man->dirty_flags |= GEOMETRY_CHANGED;
    }
  }
  else {
    new = figure_geometry(man);
    set_man_geometry(man, new);
    set_shape(man);
    if (force || oldrows != new->rows || oldcols != new->cols ||
	oldwidth != new->width || oldheight != new->height) {
      resize_window(man);
    }
  }

#if 1
  if (oldwidth != new->width || oldheight != new->height)
  {
    for (i = 0; i < NUM_CONTEXTS; i++)
    {
	    if (man->colorsets[i] >=0 &&
		(i == DEFAULT || CSET_IS_TRANSPARENT(man->colorsets[i])) &&
		Colorset[man->colorsets[i]].pixmap)
	    {
		    recreate_background(man, i);
	    }
    }
  }

  if (old_boxwidth != new->boxwidth || old_boxheight != new->boxheight)
  {
    for (i = 0; i < NUM_CONTEXTS; i++)
    {
	    if (man->colorsets[i] >= 0 && i != DEFAULT &&
		!CSET_IS_TRANSPARENT(man->colorsets[i]) &&
		Colorset[man->colorsets[i]].pixmap)
	    {
		    recreate_background(man, i);
	    }
    }
  }
#endif
}
