WriteGeometryToMIFFile(MIDDATAFile *fp)
{
    OGRGeometry         *poGeom;
    OGRPoint            *poPoint;
    OGRMultiPoint       *poMultiPoint;
    int                 nNumPoints, iPoint;


    poGeom = GetGeometryRef();
    if (poGeom && wkbFlatten(poGeom->getGeometryType()) == wkbMultiPoint)
    {
        poMultiPoint = (OGRMultiPoint*)poGeom;
        nNumPoints = poMultiPoint->getNumGeometries();

        fp->WriteLine("MultiPoint %d\n", nNumPoints);

        for(iPoint=0; iPoint < nNumPoints; iPoint++)
        {


            poGeom = poMultiPoint->getGeometryRef(iPoint);
            if (poGeom && wkbFlatten(poGeom->getGeometryType()) == wkbPoint)
            {
                poPoint = (OGRPoint*)poGeom;
                fp->WriteLine("%.15g %.15g\n",poPoint->getX(),poPoint->getY());
            }
            else
            {
                CPLError(CE_Failure, CPLE_AssertionFailed,
                         "TABMultiPoint: Missing or Invalid Geometry!");
                return -1;
            }
        }

        fp->WriteLine("    Symbol (%d,%d,%d)\n",GetSymbolNo(),GetSymbolColor(),
                      GetSymbolSize());
    }

    return 0;
}
