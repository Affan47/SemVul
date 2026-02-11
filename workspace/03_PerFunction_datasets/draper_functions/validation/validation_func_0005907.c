_clutter_paint_volume_project (ClutterPaintVolume *pv,
                               const CoglMatrix *modelview,
                               const CoglMatrix *projection,
                               const float *viewport)
{
  int transform_count;

  if (pv->is_empty)
    {

      _clutter_util_fully_transform_vertices (modelview,
                                              projection,
                                              viewport,
                                              pv->vertices,
                                              pv->vertices,
                                              1);
      return;
    }


  _clutter_paint_volume_complete (pv);


  if (G_LIKELY (pv->is_2d))
    transform_count = 4;
  else
    transform_count = 8;

  _clutter_util_fully_transform_vertices (modelview,
                                          projection,
                                          viewport,
                                          pv->vertices,
                                          pv->vertices,
                                          transform_count);

  pv->is_axis_aligned = FALSE;
}
