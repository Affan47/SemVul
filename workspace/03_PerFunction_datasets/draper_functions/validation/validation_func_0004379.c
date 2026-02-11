registryAliasLoadDatabaseconnection(
    EnsPDatabaseconnection dbc,
    EnsPDatabaseadaptor dba)
{
    char *txtdbname = NULL;

    register ajuint i = 0U;

    AjPSqlstatement sqls = NULL;
    AjISqlrow sqli       = NULL;
    AjPSqlrow sqlr       = NULL;

    AjPStr metavalue = NULL;
    AjPStr dbname    = NULL;
    AjPStr statement = NULL;

    if (!dbc)
        return ajFalse;

    if (!dba)
        return ajFalse;

    switch (ensDatabaseadaptorGetGroup(dba))
    {
        case ensEDatabaseadaptorGroupCore:

        case ensEDatabaseadaptorGroupVega:

        case ensEDatabaseadaptorGroupOtherFeatures:

        case ensEDatabaseadaptorGroupCopyDNA:


            dbname = ensDatabaseconnectionGetDatabasename(
                ensDatabaseadaptorGetDatabaseconnection(dba));

            ensDatabaseconnectionEscapeC(dbc, &txtdbname, dbname);

            for (i = 0U; registryKAliasMetaKey[i]; i++)
            {
                statement = ajFmtStr(
                    "SELECT "
                    "%s.meta.meta_value "
                    "FROM "
                    "%s.meta "
                    "WHERE "
                    "%s.meta.meta_key = '%s' "
                    "AND "
                    "%s.meta.species_id = %u",
                    txtdbname,
                    txtdbname,
                    txtdbname, registryKAliasMetaKey[i],
                    txtdbname, ensDatabaseadaptorGetIdentifier(dba));

                sqls = ensDatabaseconnectionSqlstatementNew(dbc, statement);

                sqli = ajSqlrowiterNew(sqls);

                while (!ajSqlrowiterDone(sqli))
                {
                    metavalue = ajStrNew();

                    sqlr = ajSqlrowiterGet(sqli);

                    ajSqlcolumnToStr(sqlr, &metavalue);

                    if (ajCharMatchC(registryKAliasMetaKey[i],
                                     "species.stable_id_prefix"))
                        ensRegistryAddStableidentifierprefix(dba, metavalue);
                    else
                        ensRegistryAliasAdd(ensDatabaseadaptorGetSpecies(dba),
                                            metavalue);

                    ajStrDel(&metavalue);
                }

                ajSqlrowiterDel(&sqli);

                ensDatabaseconnectionSqlstatementDel(dbc, &sqls);

                ajStrDel(&statement);
            }


            ajCharDel(&txtdbname);

            break;

        case ensEDatabaseadaptorGroupGeneticVariation:

        case ensEDatabaseadaptorGroupFunctionalGenomics:

        case ensEDatabaseadaptorGroupComparativeGenomics:

        case ensEDatabaseadaptorGroupOntology:

        case ensEDatabaseadaptorGroupQualityCheck:

        case ensEDatabaseadaptorGroupPipeline:

        case ensEDatabaseadaptorGroupHive:

        case ensEDatabaseadaptorGroupCoreExpressionEST:

        case ensEDatabaseadaptorGroupCoreExpressionGNF:

        case ensEDatabaseadaptorGroupAncestral:

        case ensEDatabaseadaptorGroupWebsite:

        case ensEDatabaseadaptorGroupProduction:


            break;

        default:

            ajWarn("registryLoadAlises got an "
                   "Ensembl Database Adaptor "
                   "with an unexpected group %d.\n",
                   ensDatabaseadaptorGetGroup(dba));
    }

    return ajTrue;
}
