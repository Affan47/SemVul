Streak_FindBoundary(StreakVars *svars, POINT_TYPE *p, VECTOR_TYPE *v, double *t)
{
    double t0, t1;

    if (svars->inside0)
	t0 = DXD_MAX_FLOAT;
    else
	if (! (*(svars->I0->currentVectorGrp->FindBoundary))
					(svars->I0, p, v, &t0))
	    return ERROR;

    if (svars->inside1)
	t1 = DXD_MAX_FLOAT;
    else
	if (! (*(svars->I1->currentVectorGrp->FindBoundary))
					(svars->I1, p, v, &t1))
	    return ERROR;

    if (t1 < t0)
	*t = t1;
    else
	*t = t0;

    if (*t == DXD_MAX_FLOAT)
    {
	DXSetError(ERROR_INTERNAL, "error in Streak_FindBoundary");
	return ERROR;
    }

    return OK;
}
