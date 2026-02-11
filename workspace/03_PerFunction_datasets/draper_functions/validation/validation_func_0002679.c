hermiteinterpolation_1d(const ColumnVector& data, int p1, int p4, float t)
  {


    float retval, r1 = 0.0, r4 = 0.0;

    if (!in_bounds(data,p1) || !in_bounds(data,p4)) {
      cerr << "Hermite Interpolation - ERROR: One or more indicies lie outside the data range. Returning ZERO" << endl;
      retval = 0.0;
    } else if ((t < 0) || (t > 1)) {
      cerr << "Hermite Interpolation - ERROR: Interpolation index must lie between 0 and 1. Returning ZERO" << endl;
      retval = 0.0;


    } else {
      r1 = 0.5 * (extrapolate_1d(data, p1) - extrapolate_1d(data, p1 - 1)) + 0.5 * (extrapolate_1d(data, p1 + 1) - extrapolate_1d(data, p1));
      r4 = 0.5 * (extrapolate_1d(data, p4) - extrapolate_1d(data, p4 - 1)) + 0.5 * (extrapolate_1d(data, p4 + 1) - extrapolate_1d(data, p4));

      float t2 = t*t; float t3 = t2*t;
      retval = (2*t3 - 3*t2 + 1)*data(p1) + (-2*t3 + 3*t2)*data(p4) + (t3 - 2*t2 + t)*r1 + (t3 - t2)*r4;
    }


    return retval;
  }
