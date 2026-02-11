message( int ev ) const
  {
    using namespace boost::system::errc;
#if defined(__PGI)
      using boost::system::errc::invalid_argument;
#endif

    static std::string unknown_err( "Unknown error" );


  # if defined(BOOST_WINDOWS_API) || defined(__hpux) || defined(__sun)\
     || (defined(__linux) && (!defined(__USE_XOPEN2K) || defined(BOOST_SYSTEM_USE_STRERROR)))\
     || (defined(__osf__) && !defined(_REENTRANT))\
     || (defined(__INTEGRITY))\
     || (defined(__vms))\
     || (defined(__QNXNTO__))
      const char * c_str = std::strerror( ev );
      return  c_str
        ? std::string( c_str )
        : unknown_err;
  # else
      char buf[64];
      char * bp = buf;
      std::size_t sz = sizeof(buf);
  #  if defined(__CYGWIN__) || defined(__USE_GNU)

      const char * c_str = strerror_r( ev, bp, sz );
      return  c_str
        ? std::string( c_str )
        : unknown_err;
  #  else

      int result;
      for (;;)
      {


  #  if defined (__sgi)
        const char * c_str = strerror( ev );
        result = 0;
      return  c_str
        ? std::string( c_str )
        : unknown_err;
  #  else
        result = strerror_r( ev, bp, sz );
  #  endif
        if (result == 0 )
          break;
        else
        {
  #  if defined(__linux)

          result = errno;
  #  endif
          if ( result !=  ERANGE ) break;
          if ( sz > sizeof(buf) ) std::free( bp );
          sz *= 2;
          if ( (bp = static_cast<char*>(std::malloc( sz ))) == 0 )
            return std::string( "ENOMEM" );
        }
      }
      std::string msg;
#   ifndef BOOST_NO_EXCEPTIONS
      try
#   endif
      {
        msg = ( ( result == invalid_argument ) ? "Unknown error" : bp );
      }

#   ifndef BOOST_NO_EXCEPTIONS

      catch(...)
      {

      }
#   endif

      if ( sz > sizeof(buf) ) std::free( bp );
      sz = 0;
      return msg;
  #  endif
  # endif
  }
