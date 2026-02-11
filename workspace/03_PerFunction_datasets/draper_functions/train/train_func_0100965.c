set_merged (FttCell * cell)
{
  GfsSolidVector * solid = GFS_STATE (cell)->solid;

  if (!gfs_cell_is_small (cell))
    solid->merged = NULL;
  else {
    FttCellNeighbors neighbor;
    gdouble abest = 0.;
    FttDirection i;

    ftt_cell_neighbors (cell, &neighbor);
    for (i = 0; i < FTT_NEIGHBORS && abest < 1.; i++)
      if (neighbor.c[i] && !GFS_CELL_IS_BOUNDARY (neighbor.c[i]) && solid->s[i] > 0.) {
	if (FTT_CELL_IS_LEAF (neighbor.c[i])) {
	  if (GFS_IS_MIXED (neighbor.c[i])) {
	    gdouble a = GFS_STATE (neighbor.c[i])->solid->a;

	    if (a > abest) {
	      abest = a;
	      solid->merged = neighbor.c[i];
	    }
	  }
	  else {
	    solid->merged = neighbor.c[i];
	    return;
	  }
	}
	else {
	  FttCellChildren child;
	  guint j, n = ftt_cell_children_direction (neighbor.c[i], FTT_OPPOSITE_DIRECTION (i), &child);

	  for (j = 0; j < n; j++)
	    if (child.c[j]) {
	      if (GFS_IS_MIXED (child.c[j])) {
		gdouble a = GFS_STATE (child.c[j])->solid->a;

		if (a > abest) {
		  abest = a;
		  solid->merged = child.c[j];
		}
	      }
	      else {
		solid->merged = child.c[j];
		return;
	      }
	    }
	}
      }
    if (abest == 0.)
      g_warning ("file %s: line %d (%s): cannot merge small cell: %g",
		 __FILE__, __LINE__, G_GNUC_PRETTY_FUNCTION,
		 solid->a);
  }
}
