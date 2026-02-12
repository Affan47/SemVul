time_t dos_to_unix_time(dosdatetime)
    ulg dosdatetime;
{
    time_t m_time;

#ifdef HAVE_MKTIME

    ZCONST time_t now = time(NULL);
    struct tm *tm;
#   define YRBASE  1900

    tm = localtime(&now);
    tm->tm_isdst = -1;


    tm->tm_year = ((int)(dosdatetime >> 25) & 0x7f) + (1980 - YRBASE);
    tm->tm_mon  = ((int)(dosdatetime >> 21) & 0x0f) - 1;
    tm->tm_mday = ((int)(dosdatetime >> 16) & 0x1f);


    tm->tm_hour = (int)((unsigned)dosdatetime >> 11) & 0x1f;
    tm->tm_min  = (int)((unsigned)dosdatetime >> 5) & 0x3f;
    tm->tm_sec  = (int)((unsigned)dosdatetime << 1) & 0x3e;

    m_time = mktime(tm);
    NATIVE_TO_TIMET(m_time)
    TTrace((stderr, "  final m_time  =       %lu\n", (ulg)m_time));

#else

    int yr, mo, dy, hh, mm, ss;
#ifdef TOPS20
#   define YRBASE  1900
    struct tmx *tmx;
    char temp[20];
#else
#   define YRBASE  1970
    int leap;
    unsigned days;
    struct tm *tm;
#if (!defined(MACOS) && !defined(RISCOS) && !defined(QDOS) && !defined(TANDEM))
#ifdef WIN32
    TIME_ZONE_INFORMATION tzinfo;
    DWORD res;
#else
#ifndef BSD4_4
#if (defined(BSD) || defined(MTS) || defined(__GO32__))
    struct timeb tbp;
#else
#ifdef DECLARE_TIMEZONE
    extern time_t timezone;
#endif
#endif
#endif
#endif
#endif
#endif


    yr = ((int)(dosdatetime >> 25) & 0x7f) + (1980 - YRBASE);
    mo = ((int)(dosdatetime >> 21) & 0x0f) - 1;
    dy = ((int)(dosdatetime >> 16) & 0x1f) - 1;


    hh = (int)((unsigned)dosdatetime >> 11) & 0x1f;
    mm = (int)((unsigned)dosdatetime >> 5) & 0x3f;
    ss = (int)((unsigned)dosdatetime & 0x1f) * 2;

#ifdef TOPS20
    tmx = (struct tmx *)malloc(sizeof(struct tmx));
    sprintf (temp, "%02d/%02d/%02d %02d:%02d:%02d", mo+1, dy+1, yr, hh, mm, ss);
    time_parse(temp, tmx, (char *)0);
    m_time = time_make(tmx);
    free(tmx);

#else


    leap = ((yr + YRBASE - 1) / 4);


    days = (yr * 365) + (leap - 492) + ydays[mo];


    if ((mo > 1) && ((yr+YRBASE)%4 == 0) && ((yr+YRBASE) != 2100))
        ++days;


    m_time = (time_t)((unsigned long)(days + dy) * 86400L +
                      (unsigned long)hh * 3600L +
                      (unsigned long)(mm * 60 + ss));

    TTrace((stderr, "dos_to_unix_time:\n"));
    TTrace((stderr, "  m_time before timezone = %lu\n", (ulg)m_time));


#if (!defined(MACOS) && !defined(RISCOS) && !defined(QDOS) && !defined(TANDEM))
#ifdef WIN32

    res = GetTimeZoneInformation(&tzinfo);
    if (res != TIME_ZONE_ID_INVALID)
    {
    m_time += 60*(tzinfo.Bias);
#else
#if (defined(BSD) || defined(MTS) || defined(__GO32__))
#ifdef BSD4_4
    if ( (dosdatetime >= DOSTIME_2038_01_18) &&
         (m_time < (time_t)0x70000000L) )
        m_time = U_TIME_T_MAX;
    if (m_time < (time_t)0L)
        m_time = S_TIME_T_MAX;
    if ((tm = localtime(&m_time)) != (struct tm *)NULL)
        m_time -= tm->tm_gmtoff;
#else
    ftime(&tbp);
    m_time += tbp.timezone * 60L;
#endif
#else


#ifndef __BEOS__
    m_time += timezone;
#endif
#endif
#endif
    TTrace((stderr, "  m_time after timezone =  %lu\n", (ulg)m_time));


#ifndef BSD4_4
    if ( (dosdatetime >= DOSTIME_2038_01_18) &&
         (m_time < (time_t)0x70000000L) )
        m_time = U_TIME_T_MAX;
    if (m_time < (time_t)0L)
        m_time = S_TIME_T_MAX;
    TIMET_TO_NATIVE(m_time)
    if (((tm = localtime((time_t *)&m_time)) != NULL) && tm->tm_isdst)
#ifdef WIN32
        m_time += 60L * tzinfo.DaylightBias;
    else
        m_time += 60L * tzinfo.StandardBias;
#else
        m_time -= 60L * 60L;
#endif
    NATIVE_TO_TIMET(m_time)
    TTrace((stderr, "  m_time after DST =       %lu\n", (ulg)m_time));
#endif
#ifdef WIN32
    }
#endif
#endif
#endif

#endif

    if ( (dosdatetime >= DOSTIME_2038_01_18) &&
         (m_time < (time_t)0x70000000L) )
        m_time = U_TIME_T_MAX;
    if (m_time < (time_t)0L)
        m_time = S_TIME_T_MAX;

    return m_time;

}
