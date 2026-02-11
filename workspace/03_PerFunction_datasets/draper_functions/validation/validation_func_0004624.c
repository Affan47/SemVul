input_stream_done(Gt_Viewer *viewer, int first_frame)
{
  viewer->can_animate = Gif_ImageCount(viewer->gfs) > 1;
  switch_animating(viewer, animating && viewer->can_animate);
  if (first_frame < 0)
    first_frame = 0;
  view_frame(viewer, first_frame);
}
