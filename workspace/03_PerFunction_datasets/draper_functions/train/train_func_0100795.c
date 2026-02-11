netclear(void)
{
    char *thisitem, *next;
    char *good;
#define	wewant(p)	((nfrontp > p) && ((*p&0xff) == IAC) && \
			 ((*(p+1)&0xff) != EC) && ((*(p+1)&0xff) != EL))

#ifdef ENCRYPTION
	thisitem = nclearto > netobuf ? nclearto : netobuf;
#else
	thisitem = netobuf;
#endif

	while ((next = nextitem(thisitem)) <= nbackp) {
	    thisitem = next;
	}


#ifdef ENCRYPTION
	good = nclearto > netobuf ? nclearto : netobuf;
#else
	good = netobuf;
#endif

	while (nfrontp > thisitem) {
	    if (wewant(thisitem)) {
		int length;

		next = thisitem;
		do {
		    next = nextitem(next);
		} while (wewant(next) && (nfrontp > next));
		length = next-thisitem;
		memmove(good, thisitem, length);
		good += length;
		thisitem = next;
	    } else {
		thisitem = nextitem(thisitem);
	    }
	}

	nbackp = netobuf;
	nfrontp = good;
	neturg = 0;
}
