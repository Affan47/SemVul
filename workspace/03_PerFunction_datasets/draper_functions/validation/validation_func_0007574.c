ensUtilityCharSort(char *string)
{
    if (!string)
        return ajFalse;

    qsort(string, strlen(string), sizeof (char), &gvCharCmp);

    return ajTrue;
}
