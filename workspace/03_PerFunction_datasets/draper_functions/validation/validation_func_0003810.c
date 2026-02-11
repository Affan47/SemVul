SetHashTableKilobytes(unsigned int size)
{

    unsigned int bytes = size * 1024;
    TranTableSize = bytes / sizeof(transTableEntryT);
    if((TranTableSize % 2) == 1)
    {
        TranTableSize--;
    }
    if(TranTable != NULL)
    {
        delete[] TranTable;
    }
    TranTable = new transTableEntryT [TranTableSize];
    ClearHashTable();
}
