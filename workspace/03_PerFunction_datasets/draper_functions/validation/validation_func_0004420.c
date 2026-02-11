init_style()
{
  if (!atom->q_flag)
    error->all(FLERR,"Pair style coul/diel requires atom attribute q");

  int irequest = neighbor->request(this);
}
