RootOfLeastSquaresFitQuadraticCurve(int n, cmsFloat64Number x[], cmsFloat64Number y[])
{
    double sum_x = 0, sum_x2 = 0, sum_x3 = 0, sum_x4 = 0;
    double sum_y = 0, sum_yx = 0, sum_yx2 = 0;
    double d, a, b, c;
    int i;
    cmsMAT3 m;
    cmsVEC3 v, res;

    if (n < 4) return 0;

    for (i=0; i < n; i++) {

        double xn = x[i];
        double yn = y[i];

        sum_x  += xn;
        sum_x2 += xn*xn;
        sum_x3 += xn*xn*xn;
        sum_x4 += xn*xn*xn*xn;

        sum_y += yn;
        sum_yx += yn*xn;
        sum_yx2 += yn*xn*xn;
    }

    _cmsVEC3init(&m.v[0], n,      sum_x,  sum_x2);
    _cmsVEC3init(&m.v[1], sum_x,  sum_x2, sum_x3);
    _cmsVEC3init(&m.v[2], sum_x2, sum_x3, sum_x4);

    _cmsVEC3init(&v, sum_y, sum_yx, sum_yx2);

    if (!_cmsMAT3solve(&res, &m, &v)) return 0;


    a = res.n[2];
    b = res.n[1];
    c = res.n[0];

    if (fabs(a) < 1.0E-10) {

        return cmsmin(0, cmsmax(50, -c/b ));
    }
    else {

         d = b*b - 4.0 * a * c;
         if (d <= 0) {
             return 0;
         }
         else {

             double rt = (-b + sqrt(d)) / (2.0 * a);

             return cmsmax(0, cmsmin(50, rt));
         }
   }

}
