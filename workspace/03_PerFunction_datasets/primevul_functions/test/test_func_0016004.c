vim_ispathsep(int c)
{
#ifdef UNIX
    return (c == '/');
#else
# ifdef BACKSLASH_IN_FILENAME
    return (c == ':' || c == '/' || c == '\\');
# else
#  ifdef VMS

    return (c == ':' || c == '[' || c == ']' || c == '/'
	    || c == '<' || c == '>' || c == '"' );
#  else
    return (c == ':' || c == '/');
#  endif
# endif
#endif
}
