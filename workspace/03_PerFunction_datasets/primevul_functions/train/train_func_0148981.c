void Emit1Gamma(cmsIOHANDLER* m, cmsToneCurve* Table)
{
    cmsUInt32Number i;
    cmsFloat64Number gamma;

    if (Table == NULL) return;

    if (Table ->nEntries <= 0) return;


    if (cmsIsToneCurveLinear(Table)) return;


    gamma = cmsEstimateGamma(Table, 0.001);
     if (gamma > 0) {
            _cmsIOPrintf(m, "{ %g exp } bind ", gamma);
            return;
     }

    _cmsIOPrintf(m, "{ ");


    EmitRangeCheck(m);


    _cmsIOPrintf(m, " [");

    for (i=0; i < Table->nEntries; i++) {
        _cmsIOPrintf(m, "%d ", Table->Table16[i]);
    }

    _cmsIOPrintf(m, "] ");

    _cmsIOPrintf(m, "dup ");
    _cmsIOPrintf(m, "length 1 sub ");
    _cmsIOPrintf(m, "3 -1 roll ");
    _cmsIOPrintf(m, "mul ");
    _cmsIOPrintf(m, "dup ");
    _cmsIOPrintf(m, "dup ");
    _cmsIOPrintf(m, "floor cvi ");
    _cmsIOPrintf(m, "exch ");
    _cmsIOPrintf(m, "ceiling cvi ");
    _cmsIOPrintf(m, "3 index ");
    _cmsIOPrintf(m, "exch ");
    _cmsIOPrintf(m, "get ");
    _cmsIOPrintf(m, "4 -1 roll ");
    _cmsIOPrintf(m, "3 -1 roll ");
    _cmsIOPrintf(m, "get ");
    _cmsIOPrintf(m, "dup ");
    _cmsIOPrintf(m, "3 1 roll ");
    _cmsIOPrintf(m, "sub ");
    _cmsIOPrintf(m, "3 -1 roll ");
    _cmsIOPrintf(m, "dup ");
    _cmsIOPrintf(m, "floor cvi ");
    _cmsIOPrintf(m, "sub ");
    _cmsIOPrintf(m, "mul ");
    _cmsIOPrintf(m, "add ");
    _cmsIOPrintf(m, "65535 div ");

    _cmsIOPrintf(m, " } bind ");
}
