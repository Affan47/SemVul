compute_scalar()
{
  invoked_scalar = update->ntimestep;

  if (id_event == NULL) return 0.0;

  double event = 0.0;
  double **xevent = fix_event->array_atom;

  double **x = atom->x;
  int *mask = atom->mask;
  tagint *image = atom->image;
  int nlocal = atom->nlocal;

  double *h = domain->h;
  double xprd = domain->xprd;
  double yprd = domain->yprd;
  double zprd = domain->zprd;
  int xbox,ybox,zbox;
  double dx,dy,dz,rsq;

  if (triclinic == 0) {
    for (int i = 0; i < nlocal; i++)
      if (mask[i] & groupbit) {
        xbox = (image[i] & IMGMASK) - IMGMAX;
        ybox = (image[i] >> IMGBITS & IMGMASK) - IMGMAX;
        zbox = (image[i] >> IMG2BITS) - IMGMAX;
        dx = x[i][0] + xbox*xprd - xevent[i][0];
        dy = x[i][1] + ybox*yprd - xevent[i][1];
        dz = x[i][2] + zbox*zprd - xevent[i][2];
        rsq = dx*dx + dy*dy + dz*dz;
        if (rsq >= displace_distsq) {
          event = 1.0;
          break;
        }
      }
  } else {
    for (int i = 0; i < nlocal; i++)
      if (mask[i] & groupbit) {
        xbox = (image[i] & IMGMASK) - IMGMAX;
        ybox = (image[i] >> IMGBITS & IMGMASK) - IMGMAX;
        zbox = (image[i] >> IMG2BITS) - IMGMAX;
        dx = x[i][0] + h[0]*xbox + h[5]*ybox + h[4]*zbox - xevent[i][0];
        dy = x[i][1] + h[1]*ybox + h[3]*zbox - xevent[i][1];
        dz = x[i][2] + h[2]*zbox - xevent[i][2];
        rsq = dx*dx + dy*dy + dz*dz;
        if (rsq >= displace_distsq) {
          event = 1.0;
          break;
        }
      }
  }

  MPI_Allreduce(&event,&scalar,1,MPI_DOUBLE,MPI_SUM,world);

  return scalar;
}
