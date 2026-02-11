ajNamQueryGetDatatypeC(const AjPQuery qry)
{
    ajuint i;
    const char* ret = NULL;

    if(ajStrGetLen(qry->DbType))
        return MAJSTRGETPTR(qry->DbType);

    for(i=0; namDbTypes[i].Name; i++)
        if(namDbTypes[i].DataType == qry->DataType)
            ret = namDbTypes[i].Name;

    return ret;
}
