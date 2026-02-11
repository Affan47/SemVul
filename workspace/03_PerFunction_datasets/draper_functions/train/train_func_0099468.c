vocisect_flags(objnum *list1, uint *flags1,
                          objnum *list2, uint *flags2)
{
    int i, j, k;

    for (i = k = 0 ; list1[i] != MCMONINV ; ++i)
    {
        for (j = 0 ; list2[j] != MCMONINV ; ++j)
        {
            if (list1[i] == list2[j])
            {
                list1[k] = list1[i];
                flags1[k] = flags1[i] | flags2[j];
                ++k;
                break;
            }
        }
    }
    list1[k] = MCMONINV;
    return(k);
}
