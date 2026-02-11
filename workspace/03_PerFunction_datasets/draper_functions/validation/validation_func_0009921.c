getDatabaseByPath(QString path)
{
    if(DatabaseInfo* dbInfo = getDatabaseInfoByPath(path))
    {
        if(dbInfo->isValid())
        {
            return dbInfo->database();
        }
    }
    return 0;
}
