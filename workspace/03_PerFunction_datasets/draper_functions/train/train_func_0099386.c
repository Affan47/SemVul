fits_unencode_url(char *inpath,
		      char *outpath,
		      int  *status)


{
    char *p;
    char *q;
    char  c;

    if(*status != 0) return(*status);

    p = inpath;
    q = outpath;


    while(*p != 0)
      {


        if (*p == HEX_ESCAPE)
	  {
            if((c = *(++p)) != 0)
	      {
		*q = (
		      (c >= '0' && c <= '9') ?
		      (c - '0') : ((c >= 'A' && c <= 'F') ?
				   (c - 'A' + 10) : (c - 'a' + 10))
		      )*16;

		if((c = *(++p)) != 0)
		  {
		    *q = *q + (
			       (c >= '0' && c <= '9') ?
		               (c - '0') : ((c >= 'A' && c <= 'F') ?
					    (c - 'A' + 10) : (c - 'a' + 10))
			       );
		    p++, q++;
		  }
	      }
	  }
	else
	  *q++ = *p++;
      }


    *q = 0;

    return(*status);
}
