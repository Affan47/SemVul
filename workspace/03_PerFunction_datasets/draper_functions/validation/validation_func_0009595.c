aitrev(x, y, prj, phi, theta)

const double x, y;
struct prjprm *prj;
double *phi, *theta;

{
   double s, u, xp, yp, z;
   const double tol = 1.0e-13;

   if (prj->flag != PRJSET) {
      if (vimosaitset(prj)) return 1;
   }

   u = 1.0 - x*x*prj->w[2] - y*y*prj->w[1];
   if (u < 0.0) {
      if (u < -tol) {
         return 2;
      }

      u = 0.0;
   }

   z = sqrt(u);
   s = z*y/prj->r0;
   if (fabs(s) > 1.0) {
      if (fabs(s) > 1.0+tol) {
         return 2;
      }
      s = copysign(1.0,s);
   }

   xp = 2.0*z*z - 1.0;
   yp = z*x*prj->w[3];
   if (xp == 0.0 && yp == 0.0) {
      *phi = 0.0;
   } else {
      *phi = 2.0*atan2deg (yp, xp);
   }
   *theta = asindeg (s);

   return 0;
}
