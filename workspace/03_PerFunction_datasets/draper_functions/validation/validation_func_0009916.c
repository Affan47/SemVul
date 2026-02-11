getCurrentThreadName()
{
#if ! defined (DCMTK_LOG4CPLUS_SINGLE_THREADED)
    log4cplus::tstring & name = log4cplus::internal::get_thread_name_str ();
    if (name.empty ())
    {
        log4cplus::tostringstream tmp;
        tmp << impl::getCurrentThreadId ();

        name = OFString(tmp.str().c_str(), tmp.str().length());
    }
#else
    static log4cplus::tstring const name (DCMTK_LOG4CPLUS_TEXT ("single"));
#endif

    return name;
}
