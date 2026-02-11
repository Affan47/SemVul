TI_buildRemoteSeries(TI_DBEntry *db, TI_StudyEntry *study)
{
    TI_GenericCallbackStruct cbs;
    DcmDataset *query = NULL;
    OFBool ok = OFTrue;

    cbs.db = NULL;
    cbs.study = study; cbs.series = NULL;

    TI_destroySeriesEntries(study);


    TI_buildSeriesQuery(&query, study);

    ok = TI_remoteFindQuery(db, query, TI_genericEntryCallback, &cbs);

    delete query;

    return ok;
}
