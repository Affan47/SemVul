create_multi_NUBspline_3d_s (NUgrid* x_grid, NUgrid* y_grid, NUgrid* z_grid,
			    BCtype_s xBC, BCtype_s yBC, BCtype_s zBC,
			    int num_splines)
{

  multi_NUBspline_3d_s* restrict spline = malloc (sizeof(multi_NUBspline_3d_s));
  if (spline == NULL)
    return spline;
  spline->spcode = MULTI_NU3D;
  spline->tcode  = SINGLE_REAL;
  spline->xBC = xBC;
  spline->yBC = yBC;
  spline->zBC = zBC;
  spline->x_grid = x_grid;
  spline->y_grid = y_grid;
  spline->z_grid = z_grid;
  spline->num_splines = num_splines;


  spline->x_basis = create_NUBasis (x_grid, xBC.lCode==PERIODIC);
  spline->y_basis = create_NUBasis (y_grid, yBC.lCode==PERIODIC);
  spline->z_basis = create_NUBasis (z_grid, zBC.lCode==PERIODIC);

  int Mx, My, Mz, Nx, Ny, Nz;
  if (xBC.lCode == PERIODIC) Mx = x_grid->num_points - 1;
  else                       Mx = x_grid->num_points;
  if (yBC.lCode == PERIODIC) My = y_grid->num_points - 1;
  else                       My = y_grid->num_points;
  if (zBC.lCode == PERIODIC) Mz = z_grid->num_points - 1;
  else                       Mz = z_grid->num_points;

  Nx = x_grid->num_points + 2;
  Ny = y_grid->num_points + 2;
  Nz = z_grid->num_points + 2;

  int N = num_splines;
#ifdef HAVE_SSE
  if (N % 4)
    N += 4 - (N % 4);
#endif

  spline->x_stride      = Ny*Nz*N;
  spline->y_stride      = Nz*N;
  spline->z_stride      = N;

#ifndef HAVE_SSE
  spline->coefs      = malloc (sizeof(float)*Nx*Ny*Nz*N);
#else
  posix_memalign ((void**)&spline->coefs, 64,
		  ((size_t)sizeof(float)*Nx*Ny*Nz*N));
  init_sse_data();
#endif

  return spline;
}
