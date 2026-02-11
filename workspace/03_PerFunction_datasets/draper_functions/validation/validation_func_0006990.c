initial_integrate_respa(int vflag, int ilevel, int flag)
{
  if (flag) return;

  dtv = step_respa[ilevel];

  if (ilevel == 0) initial_integrate(vflag);
}
