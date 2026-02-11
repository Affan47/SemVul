make_spline (unsigned int size)
{
  spline* s = (spline*)calloc (1, sizeof (spline));
  if (!s) abort();
  s->n_controls = size;
  s->control_x = (double*)calloc (s->n_controls, sizeof (double));
  s->control_y = (double*)calloc (s->n_controls, sizeof (double));

  s->n_points = 0;
  s->allocated_points = s->n_controls;
  s->points = (XPoint*)calloc (s->allocated_points, sizeof (XPoint));

  if (!s->control_x || !s->control_y || !s->points)
    abort();

  return s;
}
