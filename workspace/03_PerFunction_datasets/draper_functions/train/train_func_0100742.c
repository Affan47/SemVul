OGRGeocodeMakeRawLayer(const char* pszContent)
{
    OGRMemLayer* poLayer = new OGRMemLayer( "result", NULL, wkbNone );
    OGRFeatureDefn* poFDefn = poLayer->GetLayerDefn();
    OGRFieldDefn oFieldDefnRaw("raw", OFTString);
    poLayer->CreateField(&oFieldDefnRaw);
    OGRFeature* poFeature = new OGRFeature(poFDefn);
    poFeature->SetField("raw", pszContent);
    poLayer->CreateFeature(poFeature);
    delete poFeature;
    return (OGRLayerH) poLayer;
}
