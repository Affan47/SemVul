create_multi_UBspline_3d_c (Ugrid x_grid, Ugrid y_grid, Ugrid z_grid,
		      BCtype_c xBC, BCtype_c yBC, BCtype_c zBC,
		      int num_splines)
{

  multi_UBspline_3d_c* restrict spline = malloc (sizeof(multi_UBspline_3d_c));
  spline->spcode = MULTI_U3D;
  spline->tcode  = SINGLE_COMPLEX;
  spline->xBC = xBC;
  spline->yBC = yBC;
  spline->zBC = zBC;
  spline->num_splines = num_splines;


  int Mx = x_grid.num;  int My = y_grid.num; int Mz = z_grid.num;
  int Nx, Ny, Nz;

  if (xBC.lCode == PERIODIC || xBC.lCode == ANTIPERIODIC)
    Nx = Mx+3;
  else
    Nx = Mx+2;
  x_grid.delta = (x_grid.end - x_grid.start)/(double)(Nx-3);
  x_grid.delta_inv = 1.0/x_grid.delta;
  spline->x_grid   = x_grid;

  if (yBC.lCode == PERIODIC || yBC.lCode == ANTIPERIODIC)
    Ny = My+3;
  else
    Ny = My+2;
  y_grid.delta = (y_grid.end - y_grid.start)/(double)(Ny-3);
  y_grid.delta_inv = 1.0/y_grid.delta;
  spline->y_grid   = y_grid;

  if (zBC.lCode == PERIODIC || zBC.lCode == ANTIPERIODIC)
    Nz = Mz+3;
  else
    Nz = Mz+2;
  z_grid.delta = (z_grid.end - z_grid.start)/(double)(Nz-3);
  z_grid.delta_inv = 1.0/z_grid.delta;
  spline->z_grid   = z_grid;

  int N = spline->num_splines;
#ifdef HAVE_SSE
  if (N % 2)
    N++;
#endif

  spline->x_stride = Ny*Nz*N;
  spline->y_stride = Nz*N;
  spline->z_stride = N;

#ifndef HAVE_SSE
  spline->coefs = malloc ((size_t)2*sizeof(float)*Nx*Ny*Nz*N);
  spline->lapl3 = malloc (6*sizeof(float)*N);
#else
  posix_memalign ((void**)&spline->coefs, 64, (size_t)2*sizeof(float)*Nx*Ny*Nz*N);
  posix_memalign ((void**)&spline->lapl3, 64, 6*sizeof(float)*N);
  init_sse_data();
#endif

  return spline;
}
