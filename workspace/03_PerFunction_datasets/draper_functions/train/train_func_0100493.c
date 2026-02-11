LoadHetTable(TMPQArchive * ha)
{
    TMPQExtTable * pExtTable;
    TMPQHeader * pHeader = ha->pHeader;
    int nError = ERROR_SUCCESS;


    if(pHeader->HetTablePos64 != 0)
    {

        pExtTable = LoadExtTable(ha, pHeader->HetTablePos64, (size_t)pHeader->HetTableSize64, HET_TABLE_SIGNATURE, MPQ_KEY_HASH_TABLE);
        if(pExtTable != NULL)
        {


            ha->pHetTable = TranslateHetTable(pExtTable);
            if(ha->pHetTable != NULL)
                ha->dwMaxFileCount = ha->pHetTable->dwMaxFileCount;

            FREEMEM(pExtTable);
        }


        if(ha->pHetTable == NULL)
            nError = ERROR_FILE_CORRUPT;
    }

    return nError;
}
