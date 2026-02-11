bsd_alloc (unsigned char *options, int opt_len, int decomp)
  {
    int bits;
    unsigned int hsize, hshift, maxmaxcode;
    struct bsd_db *db;

    if (opt_len != 3 || options[0] != CI_BSD_COMPRESS || options[1] != 3
	|| BSD_VERSION(options[2]) != BSD_CURRENT_VERSION)
      {
	return NULL;
      }

    bits = BSD_NBITS(options[2]);

    switch (bits)
      {
    case 9:
    case 10:
    case 11:
    case 12:
	hsize = 5003;
	hshift = 4;
	break;
    case 13:
	hsize = 9001;
	hshift = 5;
	break;
    case 14:
	hsize = 18013;
	hshift = 6;
	break;
    case 15:
	hsize = 35023;
	hshift = 7;
	break;
    case 16:


    default:
	return NULL;
      }


    maxmaxcode = MAXCODE(bits);
    db         = kzalloc(sizeof (struct bsd_db),
					    GFP_KERNEL);
    if (!db)
      {
	return NULL;
      }


    db->dict = vmalloc(hsize * sizeof(struct bsd_dict));
    if (!db->dict)
      {
	bsd_free (db);
	return NULL;
      }


    if (!decomp)
      {
	db->lens = NULL;
      }


    else
      {
        db->lens = vmalloc((maxmaxcode + 1) * sizeof(db->lens[0]));
	if (!db->lens)
	  {
	    bsd_free (db);
	    return NULL;
	  }
      }


    db->totlen     = sizeof (struct bsd_db)   +
      		    (sizeof (struct bsd_dict) * hsize);

    db->hsize      = hsize;
    db->hshift     = hshift;
    db->maxmaxcode = maxmaxcode;
    db->maxbits    = bits;

    return (void *) db;
  }
