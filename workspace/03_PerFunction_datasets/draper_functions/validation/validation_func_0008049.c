voceq(uchar *s1, uint l1, uchar *s2, uint l2)
{
    uint i;

    if (l1 == 0 && l2 == 0)  return(TRUE);
    if (l1 == 0 || l2 == 0)  return(FALSE);
    if (l1 >= 6 && l2 >= l1) l2 = l1;
    if (l1 != l2)            return(FALSE);
    for (i = 0 ; i < l1 ; i++)
        if (*s1++ != *s2++)  return(FALSE);
    return(TRUE);
}
