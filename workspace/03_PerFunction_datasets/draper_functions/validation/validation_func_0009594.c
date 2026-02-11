GetExtent (OGREnvelope *psExtent, int bForce)

{
    if( bRegionComplete && sRegion.IsInit() )
    {
        *psExtent = sRegion;
        return OGRERR_NONE;
    }

    return OGRLayer::GetExtent( psExtent, bForce );
}
