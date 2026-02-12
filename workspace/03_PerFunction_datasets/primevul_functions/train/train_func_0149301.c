cmsBool CMSEXPORT cmsPipelineEvalReverseFloat(cmsFloat32Number Target[],
                                              cmsFloat32Number Result[],
                                              cmsFloat32Number Hint[],
                                              const cmsPipeline* lut)
{
    cmsUInt32Number  i, j;
    cmsFloat64Number  error, LastError = 1E20;
    cmsFloat32Number  fx[4], x[4], xd[4], fxd[4];
    cmsVEC3 tmp, tmp2;
    cmsMAT3 Jacobian;


    if (lut ->InputChannels != 3 && lut ->InputChannels != 4) return FALSE;
    if (lut ->OutputChannels != 3) return FALSE;


    if (Hint == NULL) {


        x[0] = x[1] = x[2] = 0.3f;
    }
    else {


        for (j=0; j < 3; j++)
            x[j] = Hint[j];
    }


    if (lut ->InputChannels == 4) {
        x[3] = Target[3];
    }
    else x[3] = 0;


    for (i = 0; i < INVERSION_MAX_ITERATIONS; i++) {


        cmsPipelineEvalFloat(x, fx, lut);


        error = EuclideanDistance(fx, Target, 3);


        if (error >= LastError)
            break;


        LastError     = error;
        for (j=0; j < lut ->InputChannels; j++)
                Result[j] = x[j];


        if (error <= 0)
            break;


        for (j = 0; j < 3; j++) {

            xd[0] = x[0];
            xd[1] = x[1];
            xd[2] = x[2];
            xd[3] = x[3];

            IncDelta(&xd[j]);

            cmsPipelineEvalFloat(xd, fxd, lut);

            Jacobian.v[0].n[j] = ((fxd[0] - fx[0]) / JACOBIAN_EPSILON);
            Jacobian.v[1].n[j] = ((fxd[1] - fx[1]) / JACOBIAN_EPSILON);
            Jacobian.v[2].n[j] = ((fxd[2] - fx[2]) / JACOBIAN_EPSILON);
        }


        tmp2.n[0] = fx[0] - Target[0];
        tmp2.n[1] = fx[1] - Target[1];
        tmp2.n[2] = fx[2] - Target[2];

        if (!_cmsMAT3solve(&tmp, &Jacobian, &tmp2))
            return FALSE;


        x[0] -= (cmsFloat32Number) tmp.n[0];
        x[1] -= (cmsFloat32Number) tmp.n[1];
        x[2] -= (cmsFloat32Number) tmp.n[2];


        for (j=0; j < 3; j++) {
            if (x[j] < 0) x[j] = 0;
            else
                if (x[j] > 1.0) x[j] = 1.0;
        }
    }

    return TRUE;
}
