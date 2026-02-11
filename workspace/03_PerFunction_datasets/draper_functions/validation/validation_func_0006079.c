inside_tri(double *x, double *v1, double *v2, double *v3,
                         double *norm)
{
  double edge[3],pvec[3],xproduct[3];

  subtract(v1,v2,edge);
  subtract(v1,x,pvec);
  cross(edge,pvec,xproduct);
  if (dotproduct(xproduct,norm) < 0.0) return 0;

  subtract(v2,v3,edge);
  subtract(v2,x,pvec);
  cross(edge,pvec,xproduct);
  if (dotproduct(xproduct,norm) < 0.0) return 0;

  subtract(v3,v1,edge);
  subtract(v3,x,pvec);
  cross(edge,pvec,xproduct);
  if (dotproduct(xproduct,norm) < 0.0) return 0;

  return 1;
}
