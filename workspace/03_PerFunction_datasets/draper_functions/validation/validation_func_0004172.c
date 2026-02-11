getEdgeMidPoint(dtPolyRef from, dtPolyRef to, float* mid) const
{
    float left[3], right[3];
    unsigned char fromType, toType;
    if (dtStatusFailed(getPortalPoints(from, to, left,right, fromType, toType)))
        return DT_FAILURE | DT_INVALID_PARAM;
    mid[0] = (left[0]+right[0])*0.5f;
    mid[1] = (left[1]+right[1])*0.5f;
    mid[2] = (left[2]+right[2])*0.5f;
    return DT_SUCCESS;
}
