cmsFloat64Number DefaultEvalParametricFn(cmsInt32Number Type, const cmsFloat64Number Params[], cmsFloat64Number R)
{
    cmsFloat64Number e, Val, disc;

    switch (Type) {


    case 1:
        if (R < 0) {

            if (fabs(Params[0] - 1.0) < MATRIX_DET_TOLERANCE)
                Val = R;
            else
                Val = 0;
        }
        else
            Val = pow(R, Params[0]);
        break;


    case -1:
         if (R < 0) {

            if (fabs(Params[0] - 1.0) < MATRIX_DET_TOLERANCE)
                Val = R;
            else
                Val = 0;
        }
        else
            Val = pow(R, 1/Params[0]);
        break;


    case 2:
        disc = -Params[2] / Params[1];

        if (R >= disc ) {

            e = Params[1]*R + Params[2];

            if (e > 0)
                Val = pow(e, Params[0]);
            else
                Val = 0;
        }
        else
            Val = 0;
        break;


     case -2:
         if (R < 0)
             Val = 0;
         else
             Val = (pow(R, 1.0/Params[0]) - Params[2]) / Params[1];

         if (Val < 0)
              Val = 0;
         break;


    case 3:
        disc = -Params[2] / Params[1];
        if (disc < 0)
            disc = 0;

        if (R >= disc) {

            e = Params[1]*R + Params[2];

            if (e > 0)
                Val = pow(e, Params[0]) + Params[3];
            else
                Val = 0;
        }
        else
            Val = Params[3];
        break;


    case -3:
        if (R >= Params[3])  {

            e = R - Params[3];

            if (e > 0)
                Val = (pow(e, 1/Params[0]) - Params[2]) / Params[1];
            else
                Val = 0;
        }
        else {
            Val = -Params[2] / Params[1];
        }
        break;


    case 4:
        if (R >= Params[4]) {

            e = Params[1]*R + Params[2];

            if (e > 0)
                Val = pow(e, Params[0]);
            else
                Val = 0;
        }
        else
            Val = R * Params[3];
        break;


    case -4:
        e = Params[1] * Params[4] + Params[2];
        if (e < 0)
            disc = 0;
        else
            disc = pow(e, Params[0]);

        if (R >= disc) {

            Val = (pow(R, 1.0/Params[0]) - Params[2]) / Params[1];
        }
        else {
            Val = R / Params[3];
        }
        break;


    case 5:
        if (R >= Params[4]) {

            e = Params[1]*R + Params[2];

            if (e > 0)
                Val = pow(e, Params[0]) + Params[5];
            else
                Val = 0;
        }
        else
            Val = R*Params[3] + Params[6];
        break;


    case -5:

        disc = Params[3] * Params[4] + Params[6];
        if (R >= disc) {

            e = R - Params[5];
            if (e < 0)
                Val = 0;
            else
                Val = (pow(e, 1.0/Params[0]) - Params[2]) / Params[1];
        }
        else {
            Val = (R - Params[6]) / Params[3];
        }
        break;


    case 6:
        e = Params[1]*R + Params[2];

        if (e < 0)
            Val = 0;
        else
            Val = pow(e, Params[0]) + Params[3];
        break;


    case -6:
        e = R - Params[3];
        if (e < 0)
            Val = 0;
        else
        Val = (pow(e, 1.0/Params[0]) - Params[2]) / Params[1];
        break;


    case 7:

       e = Params[2] * pow(R, Params[0]) + Params[3];
       if (e <= 0)
           Val = 0;
       else
           Val = Params[1]*log10(e) + Params[4];
       break;


    case -7:
       Val = pow((pow(10.0, (R-Params[4]) / Params[1]) - Params[3]) / Params[2], 1.0 / Params[0]);
       break;


   case 8:
       Val = (Params[0] * pow(Params[1], Params[2] * R + Params[3]) + Params[4]);
       break;


   case -8:

       disc = R - Params[4];
       if (disc < 0) Val = 0;
       else
           Val = (log(disc / Params[0]) / log(Params[1]) - Params[3]) / Params[2];
       break;


   case 108:
      Val = pow(1.0 - pow(1 - R, 1/Params[0]), 1/Params[0]);
      break;


    case -108:
        Val = 1 - pow(1 - pow(R, Params[0]), Params[0]);
        break;

    default:

        return 0;
    }

    return Val;
}
