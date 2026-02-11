isDisplayTransformPossible(DVPSDisplayTransform transform)
{
    if (transform == DVPSD_none)
        return OFFalse;
    return (displayFunction[transform] != NULL);
}
