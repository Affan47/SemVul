SetQuickSpatialIndexMode(GBool bQuickSpatialIndexMode)
{
    if (m_eAccessMode != TABWrite || m_numTABFiles == 0)
    {
        CPLError(CE_Failure, CPLE_AssertionFailed,
                 "SetQuickSpatialIndexMode() failed: file not opened for write access.");
        return -1;
    }

    for (int iFile=0; iFile < m_numTABFiles; iFile++)
    {
        if ( m_papoTABFiles[iFile]->SetQuickSpatialIndexMode(bQuickSpatialIndexMode) != 0)
        {

            return -1;
        }
    }

    return 0;
}
