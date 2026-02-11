file_rename (tstring const & src, tstring const & target)
{
#if defined (UNICODE) && defined (_WIN32)
    if (_wrename (src.c_str (), target.c_str ()) == 0)
        return 0;
    else
        return errno;

#else
    if (rename (DCMTK_LOG4CPLUS_TSTRING_TO_STRING (src).c_str (),
            DCMTK_LOG4CPLUS_TSTRING_TO_STRING (target).c_str ()) == 0)
        return 0;
    else
        return errno;

#endif
}
