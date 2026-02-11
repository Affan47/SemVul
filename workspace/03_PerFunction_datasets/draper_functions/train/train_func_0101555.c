sf_int_compare(void *index, Hit *hit1, Hit *hit2)
{
    long val1 = ((long *)index)[hit1->doc];
    long val2 = ((long *)index)[hit2->doc];
    if (val1 > val2) return 1;
    else if (val1 < val2) return -1;
    else return 0;
}
