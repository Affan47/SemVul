static_equal (double *position_i, double *position_j)
{
double r[3], s[3];
double x, y, z;

gamgi_math_cell_range_positive (position_i, r);
gamgi_math_cell_range_positive (position_j, s);

x = fabs (r[0] - s[0]);
y = fabs (r[1] - s[1]);
z = fabs (r[2] - s[2]);


if ((x < GAMGI_PHYS_WYCKOFF_TOLERANCE || x > 1.0 - GAMGI_PHYS_WYCKOFF_TOLERANCE)
&& (y < GAMGI_PHYS_WYCKOFF_TOLERANCE || y > 1.0 - GAMGI_PHYS_WYCKOFF_TOLERANCE)
&& (z < GAMGI_PHYS_WYCKOFF_TOLERANCE || z > 1.0 - GAMGI_PHYS_WYCKOFF_TOLERANCE))
  return TRUE;

return FALSE;
}
