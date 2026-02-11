AddFeature(const char* pszAptICAO,
                                      const char* pszRwyNum,
                                      const char* pszSubType,
                                      double dfLat,
                                      double dfLon,
                                      double dfEle,
                                      double dfTrueHeading)
{
    int nCount = 0;
    OGRFeature* poFeature = new OGRFeature(poFeatureDefn);
    poFeature->SetGeometryDirectly( new OGRPoint( dfLon, dfLat ) );
    poFeature->SetField( nCount++, pszAptICAO );
    poFeature->SetField( nCount++, pszRwyNum );
    poFeature->SetField( nCount++, pszSubType );
    poFeature->SetField( nCount++, dfEle );
    poFeature->SetField( nCount++, dfTrueHeading );

    RegisterFeature(poFeature);

    return poFeature;
}
