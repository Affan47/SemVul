OPJ_FLOAT64 opj_clock(void)
{
#ifdef _WIN32

    LARGE_INTEGER freq, t ;

    QueryPerformanceFrequency(&freq) ;


    QueryPerformanceCounter(& t) ;
    return freq.QuadPart ? ((OPJ_FLOAT64)t.QuadPart / (OPJ_FLOAT64)freq.QuadPart) :
           0;
#elif defined(__linux)
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    return ((OPJ_FLOAT64)ts.tv_sec + (OPJ_FLOAT64)ts.tv_nsec * 1e-9);
#else


    struct rusage t;
    OPJ_FLOAT64 procTime;

    getrusage(0, &t);


    procTime = (OPJ_FLOAT64)(t.ru_utime.tv_sec + t.ru_stime.tv_sec);

    return (procTime + (OPJ_FLOAT64)(t.ru_utime.tv_usec + t.ru_stime.tv_usec) *
            1e-6) ;
#endif
}
