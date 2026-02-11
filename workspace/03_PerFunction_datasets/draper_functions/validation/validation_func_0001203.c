queryGetFieldC(const AjPQuery query,
                                   const char* txt)
{
    AjPStr ret = NULL;
    AjIList iter = NULL;
    AjPQueryField field = NULL;

    iter = ajListIterNewread(query->QueryFields);

    while(!ajListIterDone(iter))
    {
        field = ajListIterGet(iter);

        if(ajStrMatchC(field->Field, txt))
        {
            ret = field->Wildquery;
            break;
        }
    }

    ajListIterDel(&iter);

    return ret;
}
