rinkj_screen_eb_init (RinkjDevice *self, const RinkjDeviceParams *params)
{
  RinkjScreenEb *z = (RinkjScreenEb *)self;
  int n_planes = params->n_planes;
  EvenBetterParams ebp;
  int strengths4[] = { 128, 50, 50, 10 };
  int strengths6[] = { 128, 50, 50, 25, 25, 10 };
  int strengths7[] = { 128, 80, 50, 50, 25, 26, 10 };
  int *strengths;

  RinkjDeviceParams out_params;

  out_params.width = floor (z->xscale * params->width + 0.5);
  out_params.height = floor (z->yscale * params->height + 0.5);
  out_params.n_planes = n_planes;
  out_params.plane_names = params->plane_names;

  z->yrem = params->height >> 1;

  if (n_planes == 4)
    strengths = strengths4;
  else if (n_planes == 6)
    strengths = strengths6;
  else if (n_planes == 7)
    strengths = strengths7;

  ebp.source_width = params->width;
  ebp.dest_width = out_params.width;
  ebp.levels = 1 << z->bps;
  ebp.luts = z->lut;
  ebp.n_planes = n_planes;
  ebp.aspect = z->aspect;
  ebp.rbscale = 0.0;
  ebp.strengths = strengths;
  ebp.rand_scale = 0;
  ebp.even_c1_scale = 1;
  ebp.do_shadows = 0;
  ebp.dump_file = NULL;
  ebp.gamma = 0;
  z->dither = even_better_new (&ebp);

  z->width_out = out_params.width;
  z->height_in = params->height;
  z->height_out = out_params.height;
  z->n_planes = n_planes;
#ifdef DEBUG_OUT
  fprintf (stdout, "P5\n%d %d\n255\n", params->width, params->height);
#endif
  return rinkj_device_init (z->dev_out, &out_params);
}
