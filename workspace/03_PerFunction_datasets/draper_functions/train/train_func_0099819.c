compute(int eflag, int vflag)
{
  int i1,i2,i3,i4,n,type;
  double vb1x,vb1y,vb1z,vb2x,vb2y,vb2z,vb3x,vb3y,vb3z;

  if (eflag || vflag) ev_setup(eflag,vflag);
  else evflag = 0;

  double **x = atom->x;
  int **improperlist = neighbor->improperlist;
  int nimproperlist = neighbor->nimproperlist;

  for (n = 0; n < nimproperlist; n++) {
    i1 = improperlist[n][0];
    i2 = improperlist[n][1];
    i3 = improperlist[n][2];
    i4 = improperlist[n][3];
    type = improperlist[n][4];


    vb1x = x[i2][0] - x[i1][0];
    vb1y = x[i2][1] - x[i1][1];
    vb1z = x[i2][2] - x[i1][2];


    vb2x = x[i3][0] - x[i1][0];
    vb2y = x[i3][1] - x[i1][1];
    vb2z = x[i3][2] - x[i1][2];


    vb3x = x[i4][0] - x[i1][0];
    vb3y = x[i4][1] - x[i1][1];
    vb3z = x[i4][2] - x[i1][2];

    addone(i1,i2,i3,i4, type,evflag,eflag,
           vb1x, vb1y, vb1z,
           vb2x, vb2y, vb2z,
           vb3x, vb3y, vb3z);
    if ( all[type] ) {
      addone(i1,i4,i2,i3, type,evflag,eflag,
             vb3x, vb3y, vb3z,
             vb1x, vb1y, vb1z,
             vb2x, vb2y, vb2z);
      addone(i1,i3,i4,i2, type,evflag,eflag,
             vb2x, vb2y, vb2z,
             vb3x, vb3y, vb3z,
             vb1x, vb1y, vb1z);
    }
  }
}
