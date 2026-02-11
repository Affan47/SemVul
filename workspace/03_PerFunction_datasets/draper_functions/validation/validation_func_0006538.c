SetCGATSfld(const char* Col, cmsFloat64Number Val)
{
    if (lQuantize)
        Val = floor(Val + 0.5);

    if (!cmsIT8SetDataDbl(hIT8out, CGATSPatch, Col, Val)) {
        FatalError("couldn't set '%s' on output cgats '%s'", Col, CGATSoutFilename);
    }
}
