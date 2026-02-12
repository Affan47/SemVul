static inline void ClampUpAxes(const double dux,
			       const double dvx,
			       const double duy,
			       const double dvy,
			       double *major_mag,
			       double *minor_mag,
			       double *major_unit_x,
			       double *major_unit_y,
			       double *minor_unit_x,
			       double *minor_unit_y)
{


  const double a = dux;
  const double b = duy;
  const double c = dvx;
  const double d = dvy;


  const double aa = a*a;
  const double bb = b*b;
  const double cc = c*c;
  const double dd = d*d;


  const double n11 = aa+bb;
  const double n12 = a*c+b*d;
  const double n21 = n12;
  const double n22 = cc+dd;
  const double det = a*d-b*c;
  const double twice_det = det+det;
  const double frobenius_squared = n11+n22;
  const double discriminant =
    (frobenius_squared+twice_det)*(frobenius_squared-twice_det);


  const double sqrt_discriminant =
    sqrt(discriminant > 0.0 ? discriminant : 0.0);


  const double s1s1 = 0.5*(frobenius_squared+sqrt_discriminant);


  const double s2s2 = 0.5*(frobenius_squared-sqrt_discriminant);
  const double s1s1minusn11 = s1s1-n11;
  const double s1s1minusn22 = s1s1-n22;


  const double s1s1minusn11_squared = s1s1minusn11*s1s1minusn11;
  const double s1s1minusn22_squared = s1s1minusn22*s1s1minusn22;


  const double temp_u11 =
    ( (s1s1minusn11_squared>=s1s1minusn22_squared) ? n12 : s1s1minusn22 );
  const double temp_u21 =
    ( (s1s1minusn11_squared>=s1s1minusn22_squared) ? s1s1minusn11 : n21 );
  const double norm = sqrt(temp_u11*temp_u11+temp_u21*temp_u21);


  const double u11 = ( (norm>0.0) ? temp_u11/norm : 1.0 );
  const double u21 = ( (norm>0.0) ? temp_u21/norm : 0.0 );


  *major_mag = ( (s1s1<=1.0) ? 1.0 : sqrt(s1s1) );
  *minor_mag = ( (s2s2<=1.0) ? 1.0 : sqrt(s2s2) );


  *major_unit_x = u11;
  *major_unit_y = u21;
  *minor_unit_x = -u21;
  *minor_unit_y = u11;
}
