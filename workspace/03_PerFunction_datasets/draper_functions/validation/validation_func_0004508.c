ensGvindividualadaptorFetchReference(
    EnsPGvindividualadaptor gvia,
    EnsPGvindividual *Pgvi)
{
    AjBool result = AJFALSE;

    AjPList gvis = NULL;

    EnsPGvindividual gvi = NULL;

    if (!gvia)
        return ajFalse;

    if (!Pgvi)
        return ajFalse;

    gvis = ajListNew();

    result = ensGvindividualadaptorFetchAllbyDisplay(
        gvia,
        ensEGvsampleDisplayReference,
        gvis);


    ajListPop(gvis, (void **) Pgvi);

    while (ajListPop(gvis, (void **) &gvi))
        ensGvindividualDel(&gvi);

    ajListFree(&gvis);

    return result;
}
