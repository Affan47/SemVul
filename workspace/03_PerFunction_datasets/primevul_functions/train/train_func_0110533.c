cmsBool CMSEXPORT cmsDesaturateLab(cmsCIELab* Lab,
                                   double amax, double amin,
                                   double bmax, double bmin)
{


    if (Lab -> L < 0) {

        Lab-> L = Lab->a = Lab-> b = 0.0;
        return FALSE;
    }


    if (Lab->L > 100)
        Lab -> L = 100;


    if (Lab -> a < amin || Lab->a > amax||
        Lab -> b < bmin || Lab->b > bmax) {

            cmsCIELCh LCh;
            double h, slope;


            if (Lab -> a == 0.0) {


                Lab -> b = Lab->b < 0 ? bmin : bmax;
                return TRUE;
            }

            cmsLab2LCh(&LCh, Lab);

            slope = Lab -> b / Lab -> a;
            h = LCh.h;


            if ((h >= 0. && h < 45.) ||
                (h >= 315 && h <= 360.)) {


                    Lab -> a = amax;
                    Lab -> b = amax * slope;
            }
            else
                if (h >= 45. && h < 135.)
                {

                    Lab -> b = bmax;
                    Lab -> a = bmax / slope;
                }
                else
                    if (h >= 135. && h < 225.) {

                        Lab -> a = amin;
                        Lab -> b = amin * slope;

                    }
                    else
                        if (h >= 225. && h < 315.) {

                            Lab -> b = bmin;
                            Lab -> a = bmin / slope;
                        }
                        else  {
                            cmsSignalError(0, cmsERROR_RANGE, "Invalid angle");
                            return FALSE;
                        }

    }

    return TRUE;
}
