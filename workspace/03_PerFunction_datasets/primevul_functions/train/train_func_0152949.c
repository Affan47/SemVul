cmsFloat64Number EvalSegmentedFn(const cmsToneCurve *g, cmsFloat64Number R)
{
    int i;

    for (i = g ->nSegments-1; i >= 0 ; --i) {


        if ((R > g ->Segments[i].x0) && (R <= g ->Segments[i].x1)) {


            if (g ->Segments[i].Type == 0) {

                cmsFloat32Number R1 = (cmsFloat32Number) (R - g ->Segments[i].x0) / (g ->Segments[i].x1 - g ->Segments[i].x0);
                cmsFloat32Number Out;


                g ->SegInterp[i]-> Table = g ->Segments[i].SampledPoints;

                g ->SegInterp[i] -> Interpolation.LerpFloat(&R1, &Out, g ->SegInterp[i]);

                return Out;
            }
            else
                return g ->Evals[i](g->Segments[i].Type, g ->Segments[i].Params, R);
        }
    }

    return MINUS_INF;
}
