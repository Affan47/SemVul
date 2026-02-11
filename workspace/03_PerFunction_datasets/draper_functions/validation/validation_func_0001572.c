ajDmxScophitListCopy(const AjPList scophits)
{
    AjPList list = NULL;
    AjIList iter = NULL;

    AjPScophit oldscophit = NULL;
    AjPScophit newscophit = NULL;


    if(!scophits)
    {
        ajWarn("Bad arg's passed to ajDmxScophitListCopy\n");
        return NULL;
    }


    list = ajListNew();


    iter = ajListIterNewread(scophits);


    while((oldscophit = (AjPScophit)ajListIterGet(iter)))
    {
        newscophit = ajDmxScophitNew();

        ajDmxScophitCopy(&newscophit, oldscophit);


        ajListPushAppend(list, newscophit);
    }

    ajListIterDel(&iter);

    return list;
}
