FastHufDecoder::enabled()
{
    #if defined(__INTEL_COMPILER) || defined(__GNUC__)


        #if defined (__i386__) || defined(__x86_64__)
            return true;
        #else
            return false;
        #endif

    #elif defined (_MSC_VER)


        #if defined (_M_IX86) || defined(_M_X64)
            return true;
        #else
            return false;
        #endif

    #else


        return false;
    #endif
}
