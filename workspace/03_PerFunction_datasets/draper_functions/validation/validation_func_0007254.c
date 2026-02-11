static_pbc_out (int slices, double box, int *n)
{
double s = 0.0;

if (*n < 0) { *n += slices; s = -box; }
if (*n > slices - 1) { *n -= slices; s = box; }

return s;
}
