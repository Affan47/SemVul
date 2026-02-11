errordefect( double *d, int n)

{
  int i,j;
  double diff;

  diff=0.;
  for(i=0; i<n; i++){
    for(j=0; j<n; j++){
      diff += d[index2d(i,j,n)]*d[index2d(i,j,n)];
    }
  }
  return(diff);
}
