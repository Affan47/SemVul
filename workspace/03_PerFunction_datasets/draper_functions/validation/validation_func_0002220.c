airSgnPow(double v, double p) {

  return (p == 1
          ? v
          : (v >= 0
             ? pow(v, p)
             : -pow(-v, p)));
}
