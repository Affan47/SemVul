laser_angle_new(double x, double y, double speed, int theta,
                double length, int color)
{

  if (speed < NEAR_ZERO)
  {
    fprintf(stderr, "laser_angle_new: speed is non-positive (%f)\n",
            speed);
    return NULL;
  }
  if (length <= NEAR_ZERO)
  {
    fprintf(stderr, "laser_angle_new: length is non-positive (%f)\n",
            length);
    return NULL;
  }

  return laser_new(x, y,
                   speed * tenm_cos(theta),
                   speed * tenm_sin(theta),
                   length * tenm_cos(theta),
                   length * tenm_sin(theta),
                   color, -2, 0);
}
