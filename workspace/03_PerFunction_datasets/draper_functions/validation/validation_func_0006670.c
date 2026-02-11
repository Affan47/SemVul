AddFeature  (const char* pszAptICAO,
                                        const char* pszRwyNum,
                                        double dfLat,
                                        double dfLon,
                                        double dfWidth,
                                        const char* pszSurfaceType,
                                        const char* pszShoulderType,
                                        double dfSmoothness,
                                        int bHasCenterLineLights,
                                        const char* pszEdgeLighting,
                                        int bHasDistanceRemainingSigns,
                                        double dfDisplacedThresholdLength,
                                        double dfStopwayLength,
                                        const char* pszMarkings,
                                        const char* pszApproachLightingCode,
                                        int bHasTouchdownLights,
                                        const char* pszREIL)
{
    int nCount = 0;
    OGRFeature* poFeature = new OGRFeature(poFeatureDefn);
    poFeature->SetField( nCount++, pszAptICAO );
    poFeature->SetField( nCount++, pszRwyNum );
    poFeature->SetField( nCount++, dfWidth );
    poFeature->SetGeometryDirectly( new OGRPoint( dfLon, dfLat ) );
    poFeature->SetField( nCount++, pszSurfaceType );
    poFeature->SetField( nCount++, pszShoulderType );
    poFeature->SetField( nCount++, dfSmoothness );
    poFeature->SetField( nCount++, bHasCenterLineLights );
    poFeature->SetField( nCount++, pszEdgeLighting );
    poFeature->SetField( nCount++, bHasDistanceRemainingSigns );
    poFeature->SetField( nCount++, dfDisplacedThresholdLength );
    poFeature->SetField( nCount++, FALSE);
    poFeature->SetField( nCount++, dfStopwayLength );
    poFeature->SetField( nCount++, pszMarkings );
    poFeature->SetField( nCount++, pszApproachLightingCode );
    poFeature->SetField( nCount++, bHasTouchdownLights );
    poFeature->SetField( nCount++, pszREIL );

    RegisterFeature(poFeature);

    return poFeature;
}
