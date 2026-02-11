DBFGetFieldIndex(DBFHandle psDBF, const char *pszFieldName)

{
    char          name[12], name1[12], name2[12];
    int           i;

    strncpy(name1, pszFieldName,11);
    name1[11] = '\0';
    str_to_upper(name1);

    for( i = 0; i < DBFGetFieldCount(psDBF); i++ )
    {
        DBFGetFieldInfo( psDBF, i, name, NULL, NULL );
        strncpy(name2,name,11);
        str_to_upper(name2);

        if(!strncmp(name1,name2,10))
            return(i);
    }
    return(-1);
}
