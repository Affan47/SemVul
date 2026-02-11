a_range_reduction( ConstReal aa )
{
    if (aa > MIN_ANGLE && aa<MAX_ANGLE) return aa;

    Real a = aa;
    while (a <= MIN_ANGLE) a += ONE_ROTATION;
    while (a >= MAX_ANGLE) a -= ONE_ROTATION;
    return a;
}
