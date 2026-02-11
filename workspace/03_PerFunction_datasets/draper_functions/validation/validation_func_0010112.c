Exists(int docID)
{
    String key((char *) &docID, sizeof docID);
    return dbf->Exists(key);
}
