getidname(int idnumber) const
{
    if (idnumber<nvars)
        return vararray[idnumber];
    else
    {
        printf("Error in getidname: idnumber %d is larger than nvars %d\n",
               idnumber, nvars);
        return 0;
    }
}
