ClearSpatialFIDs()
{
    if ( panSpatialFIDs != NULL )
    {
        CPLDebug("SHAPE", "Clear panSpatialFIDs");
        free( panSpatialFIDs );
    }
    panSpatialFIDs = NULL;
    nSpatialFIDCount = 0;

    delete m_poFilterGeomLastValid;
    m_poFilterGeomLastValid = NULL;
}
