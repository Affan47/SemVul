GEOSRelateBoundaryNodeRule_r(GEOSContextHandle_t extHandle, const Geometry *g1, const Geometry *g2, int bnr)
{
    if ( 0 == extHandle )
    {
        return NULL;
    }

    GEOSContextHandleInternal_t *handle = 0;
    handle = reinterpret_cast<GEOSContextHandleInternal_t*>(extHandle);
    if ( 0 == handle->initialized )
    {
        return NULL;
    }

    try
    {
        using geos::operation::relate::RelateOp;
        using geos::geom::IntersectionMatrix;
        using geos::algorithm::BoundaryNodeRule;

        IntersectionMatrix* im;
        switch (bnr) {
          case GEOSRELATE_BNR_MOD2:
            im = RelateOp::relate(g1, g2,
                BoundaryNodeRule::getBoundaryRuleMod2());
            break;
          case GEOSRELATE_BNR_ENDPOINT:
            im = RelateOp::relate(g1, g2,
                BoundaryNodeRule::getBoundaryEndPoint());
            break;
          case GEOSRELATE_BNR_MULTIVALENT_ENDPOINT:
            im = RelateOp::relate(g1, g2,
                BoundaryNodeRule::getBoundaryMultivalentEndPoint());
            break;
          case GEOSRELATE_BNR_MONOVALENT_ENDPOINT:
            im = RelateOp::relate(g1, g2,
                BoundaryNodeRule::getBoundaryMonovalentEndPoint());
            break;
          default:
            handle->ERROR_MESSAGE("Invalid boundary node rule %d", bnr);
            return 0;
            break;
        }

        if (0 == im) return 0;

        char *result = gstrdup(im->toString());

        delete im;
        im = 0;

        return result;
    }
    catch (const std::exception &e)
    {
        handle->ERROR_MESSAGE("%s", e.what());
    }
    catch (...)
    {
        handle->ERROR_MESSAGE("Unknown exception thrown");
    }

    return NULL;
}
