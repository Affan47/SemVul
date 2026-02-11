cogl_vector3_normalize (float *vector)
{
  float mag_squared =
    vector[X] * vector[X] +
    vector[Y] * vector[Y] +
    vector[Z] * vector[Z];

  if (mag_squared > 0.0f)
    {
      float one_over_mag = 1.0f / sqrtf (mag_squared);
      vector[X] *= one_over_mag;
      vector[Y] *= one_over_mag;
      vector[Z] *= one_over_mag;
    }
}
