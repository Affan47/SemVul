bool SplashRadialPattern::getParameter(double xs, double ys, double *t) {
  double b, c, s0, s1;


  xs -= x0;
  ys -= y0;


  b = xs*dx + ys*dy + r0*dr;
  c = xs*xs + ys*ys - r0*r0;

  if (fabs(a) <= RADIAL_EPSILON) {


    if (fabs(b) <= RADIAL_EPSILON)
      return false;

    s0 = s1 = 0.5 * c / b;
  } else {
    double d;

    d = b*b - a*c;
    if (d < 0)
      return false;

    d = sqrt (d);
    s0 = b + d;
    s1 = b - d;


    s0 *= inva;
    s1 *= inva;
  }

  if (r0 + s0 * dr >= 0) {
    if (0 <= s0 && s0 <= 1) {
      *t = t0 + dt * s0;
      return true;
    } else if (s0 < 0 && shading->getExtend0()) {
      *t = t0;
      return true;
    } else if (s0 > 1 && shading->getExtend1()) {
      *t = t1;
      return true;
    }
  }

  if (r0 + s1 * dr >= 0) {
    if (0 <= s1 && s1 <= 1) {
      *t = t0 + dt * s1;
      return true;
    } else if (s1 < 0 && shading->getExtend0()) {
      *t = t0;
      return true;
    } else if (s1 > 1 && shading->getExtend1()) {
      *t = t1;
      return true;
    }
  }

  return false;
}
