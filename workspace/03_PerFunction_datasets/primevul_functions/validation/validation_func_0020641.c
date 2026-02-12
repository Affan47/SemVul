time_differs(long t1, long t2)
{
#if defined(__linux__) || defined(MSWIN)


    return (t1 - t2 > 1 || t2 - t1 > 1);
#else
    return (t1 != t2);
#endif
}
