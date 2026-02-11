intersects(const PlaneBoundedVolume& pbv)
{

    if (mEnabled)
    {
        switch(mType)
        {
        case PORTAL_TYPE_QUAD:
            {

                if (!pbv.intersects(mDerivedSphere))
                {
                    return false;
                }


                PlaneList::const_iterator it = pbv.planes.begin();
                while (it != pbv.planes.end())
                {
                    const Plane& plane = *it;

                    bool allOutside = true;
                    for (int i=0;i<4;i++)
                    {
                        if (plane.getSide(mDerivedCorners[i]) != pbv.outside)
                        {
                            allOutside = false;
                        }
                    }
                    if (allOutside)
                    {
                        return false;
                    }
                    it++;
                };
            }
            break;
        case PORTAL_TYPE_AABB:
            {
                AxisAlignedBox aabb;
                aabb.setExtents(mDerivedCorners[0], mDerivedCorners[1]);
                if (!pbv.intersects(aabb))
                {
                    return false;
                }
            }
            break;
        case PORTAL_TYPE_SPHERE:
            if (!pbv.intersects(mDerivedSphere))
            {
                return false;
            }
            break;
        }
    }
    return false;
}
