iobuf_get_filelength (IOBUF a, int *overflow )
{
    struct stat st;

    if (overflow)
      *overflow = 0;

    if (a->directfp)
      {
	FILE *fp = a->directfp;

#ifdef __VMS


        return vms_file_size (fileno( fp));
#else
        if( !fstat(fileno(fp), &st) )
           return st.st_size;
	log_error("fstat() failed: %s\n", strerror(errno) );
	return 0;
#endif
    }


    for( ; a; a = a->chain )
	if( !a->chain && a->filter == file_filter ) {
	    file_filter_ctx_t *b = a->filter_ov;
	    FILEP_OR_FD fp = b->fp;

#if defined(HAVE_DOSISH_SYSTEM) && !defined(FILE_FILTER_USES_STDIO)
            ulong size;
            static int (* __stdcall get_file_size_ex)
              (void *handle, LARGE_INTEGER *size);
            static int get_file_size_ex_initialized;

            if (!get_file_size_ex_initialized)
              {
                void *handle;

                handle = dlopen ("kernel32.dll", RTLD_LAZY);
                if (handle)
                  {
                    get_file_size_ex = dlsym (handle, "GetFileSizeEx");
                    if (!get_file_size_ex)
                    dlclose (handle);
                  }
                get_file_size_ex_initialized = 1;
              }

            if (get_file_size_ex)
              {


                LARGE_INTEGER size;

                if (get_file_size_ex (fp, &size))
                  {
                    if (!size.u.HighPart)
                      return size.u.LowPart;
                    if (overflow)
                      *overflow = 1;
                    return 0;
                  }
              }
            else
              {
                if  ((size=GetFileSize (fp, NULL)) != 0xffffffff)
                  return size;
              }
            log_error ("GetFileSize for handle %p failed: %s\n",
                       fp, w32_strerror (0));
#elif defined(__VMS)
            return vms_file_size (my_fileno (fp));
#else
            if( !fstat(my_fileno(fp), &st) )
		return st.st_size;
	    log_error("fstat() failed: %s\n", strerror(errno) );
#endif
	    break;
	}

    return 0;
}
