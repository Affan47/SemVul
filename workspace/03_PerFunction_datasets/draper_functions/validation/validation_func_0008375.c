add_axisymmetric_term (FttCell * cell, FluxPar * p)
{
  GfsFunction * alpha = gfs_object_simulation (p->s)->physical_params.alpha;
  gdouble a = GFS_IS_MIXED (cell) ? GFS_STATE (cell)->solid->a : 1.;
  GFS_VALUE (cell, p->sv) -=
    (alpha ? gfs_function_value (alpha, cell) : 1.)*
    2.*gfs_source_diffusion_cell (GFS_SOURCE_DIFFUSION (p->s), cell)*
    GFS_VALUE (cell, p->v)*
    a*a/gfs_domain_cell_fraction (p->v->domain, cell)*
    p->dt;
}
